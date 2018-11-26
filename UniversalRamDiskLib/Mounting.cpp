#include "Mounting.h"
#include "Log.h"
#include "GlobalMountEvent.h"

#include <string>
#include "dokan/dokan.h"

UniversalRamDisk* MountedDisk::m_ramDisk = nullptr;
GlobalMountEvent* MountedDisk::m_mountEvent = nullptr;

static void FillDokanOperations(DOKAN_OPERATIONS& dokanOperations)
{
	NTSTATUS DOKAN_CALLBACK URAMD_CreateFile(LPCWSTR FileName, PDOKAN_IO_SECURITY_CONTEXT SecurityContext, ACCESS_MASK DesiredAccess, ULONG FileAttributes, ULONG ShareAccess, ULONG CreateDisposition, ULONG CreateOptions, PDOKAN_FILE_INFO DokanFileInfo);
	void DOKAN_CALLBACK URAMD_Cleanup(LPCWSTR FileName, PDOKAN_FILE_INFO DokanFileInfo);
	void DOKAN_CALLBACK URAMD_CloseFile(LPCWSTR FileName, PDOKAN_FILE_INFO DokanFileInfo);
	NTSTATUS DOKAN_CALLBACK URAMD_ReadFile(LPCWSTR FileName, LPVOID Buffer, DWORD BufferLength, LPDWORD ReadLength, LONGLONG Offset, PDOKAN_FILE_INFO DokanFileInfo);
	NTSTATUS DOKAN_CALLBACK URAMD_WriteFile(LPCWSTR FileName, LPCVOID Buffer, DWORD NumberOfBytesToWrite, LPDWORD NumberOfBytesWritten, LONGLONG Offset, PDOKAN_FILE_INFO DokanFileInfo);
	NTSTATUS DOKAN_CALLBACK URAMD_FlushFileBuffers(LPCWSTR FileName, PDOKAN_FILE_INFO DokanFileInfo);
	NTSTATUS DOKAN_CALLBACK URAMD_GetFileInformation(LPCWSTR FileName, LPBY_HANDLE_FILE_INFORMATION Buffer, PDOKAN_FILE_INFO DokanFileInfo);
	NTSTATUS DOKAN_CALLBACK URAMD_FindFiles(LPCWSTR FileName, PFillFindData FillFindData, PDOKAN_FILE_INFO DokanFileInfo);
	NTSTATUS DOKAN_CALLBACK URAMD_FindFilesWithPattern(LPCWSTR PathName, LPCWSTR SearchPattern, PFillFindData FillFindData, PDOKAN_FILE_INFO DokanFileInfo);
	NTSTATUS DOKAN_CALLBACK URAMD_SetFileAttributes(LPCWSTR FileName, DWORD FileAttributes, PDOKAN_FILE_INFO DokanFileInfo);
	NTSTATUS DOKAN_CALLBACK URAMD_SetFileTime(LPCWSTR FileName, CONST FILETIME *CreationTime, CONST FILETIME *LastAccessTime, CONST FILETIME *LastWriteTime, PDOKAN_FILE_INFO DokanFileInfo);
	NTSTATUS DOKAN_CALLBACK URAMD_DeleteFile(LPCWSTR FileName, PDOKAN_FILE_INFO DokanFileInfo);
	NTSTATUS DOKAN_CALLBACK URAMD_DeleteDirectory(LPCWSTR FileName, PDOKAN_FILE_INFO DokanFileInfo);
	NTSTATUS DOKAN_CALLBACK URAMD_MoveFile(LPCWSTR FileName, LPCWSTR NewFileName, BOOL ReplaceIfExisting, PDOKAN_FILE_INFO DokanFileInfo);
	NTSTATUS DOKAN_CALLBACK URAMD_SetEndOfFile(LPCWSTR FileName, LONGLONG ByteOffset, PDOKAN_FILE_INFO DokanFileInfo);
	NTSTATUS DOKAN_CALLBACK URAMD_SetAllocationSize(LPCWSTR FileName, LONGLONG AllocSize, PDOKAN_FILE_INFO DokanFileInfo);
	NTSTATUS DOKAN_CALLBACK URAMD_LockFile(LPCWSTR FileName, LONGLONG ByteOffset, LONGLONG Length, PDOKAN_FILE_INFO DokanFileInfo);
	NTSTATUS DOKAN_CALLBACK URAMD_UnlockFile(LPCWSTR FileName, LONGLONG ByteOffset, LONGLONG Length, PDOKAN_FILE_INFO DokanFileInfo);
	NTSTATUS DOKAN_CALLBACK URAMD_GetDiskFreeSpace(PULONGLONG FreeBytesAvailable, PULONGLONG TotalNumberOfBytes, PULONGLONG TotalNumberOfFreeBytes, PDOKAN_FILE_INFO DokanFileInfo);
	NTSTATUS DOKAN_CALLBACK URAMD_GetVolumeInformation(LPWSTR VolumeNameBuffer, DWORD VolumeNameSize, LPDWORD VolumeSerialNumber, LPDWORD MaximumComponentLength, LPDWORD FileSystemFlags, LPWSTR FileSystemNameBuffer, DWORD FileSystemNameSize, PDOKAN_FILE_INFO DokanFileInfo);
	NTSTATUS DOKAN_CALLBACK URAMD_Mounted(PDOKAN_FILE_INFO DokanFileInfo);
	NTSTATUS DOKAN_CALLBACK URAMD_Unmounted(PDOKAN_FILE_INFO DokanFileInfo);
	NTSTATUS DOKAN_CALLBACK URAMD_GetFileSecurity(LPCWSTR FileName, PSECURITY_INFORMATION SecurityInformation, PSECURITY_DESCRIPTOR SecurityDescriptor, ULONG BufferLength, PULONG LengthNeeded, PDOKAN_FILE_INFO DokanFileInfo);
	NTSTATUS DOKAN_CALLBACK URAMD_SetFileSecurity(LPCWSTR FileName, PSECURITY_INFORMATION SecurityInformation, PSECURITY_DESCRIPTOR SecurityDescriptor, ULONG BufferLength, PDOKAN_FILE_INFO DokanFileInfo);
	NTSTATUS DOKAN_CALLBACK URAMD_FindStreams(LPCWSTR FileName, PFillFindStreamData FillFindStreamData, PDOKAN_FILE_INFO DokanFileInfo);

	memset(&dokanOperations, 0, sizeof(DOKAN_OPTIONS));
	dokanOperations.ZwCreateFile = URAMD_CreateFile;
	dokanOperations.Cleanup = URAMD_Cleanup;
	dokanOperations.CloseFile = URAMD_CloseFile;
	dokanOperations.ReadFile = URAMD_ReadFile;
	dokanOperations.WriteFile = URAMD_WriteFile;
	dokanOperations.FlushFileBuffers = URAMD_FlushFileBuffers;
	dokanOperations.GetFileInformation = URAMD_GetFileInformation;
	dokanOperations.FindFiles = URAMD_FindFiles;
	dokanOperations.FindFilesWithPattern = URAMD_FindFilesWithPattern;
	dokanOperations.SetFileAttributes = URAMD_SetFileAttributes;
	dokanOperations.SetFileTime = URAMD_SetFileTime;
	dokanOperations.DeleteFile = URAMD_DeleteFile;
	dokanOperations.DeleteDirectory = URAMD_DeleteDirectory;
	dokanOperations.MoveFile = URAMD_MoveFile;
	dokanOperations.SetEndOfFile = URAMD_SetEndOfFile;
	dokanOperations.SetAllocationSize = URAMD_SetAllocationSize;
	dokanOperations.LockFile = URAMD_LockFile;
	dokanOperations.UnlockFile = URAMD_UnlockFile;
	dokanOperations.GetDiskFreeSpace = URAMD_GetDiskFreeSpace;
	dokanOperations.GetVolumeInformation = URAMD_GetVolumeInformation;
	dokanOperations.Mounted = URAMD_Mounted;
	dokanOperations.Unmounted = URAMD_Unmounted;
	dokanOperations.GetFileSecurity = URAMD_GetFileSecurity;
	dokanOperations.SetFileSecurity = URAMD_SetFileSecurity;
	dokanOperations.FindStreams = URAMD_FindStreams;
}

bool MountedDisk::ValidateMountPointAndCreateEvent(wchar_t driveLetter)
{
	const auto driveType = GetDriveType(DriveLetterToRootPath(driveLetter).c_str());
	if (driveType != DRIVE_NO_ROOT_DIR)
	{
		if (driveType != DRIVE_UNKNOWN)
			Log("Invalid drive letter: ", driveLetter);
		else
			Log("Drive letter already taken: ", driveLetter);
		return false;
	}

	m_mountEvent = new GlobalMountEvent(driveLetter);
	return true;
}

void MountedDisk::MountDiskAndRun(UniversalRamDisk& ramDisk, wchar_t driveLetter)
{
	if (!ValidateMountPointAndCreateEvent(driveLetter))
		return;

	DOKAN_OPTIONS dokanOptions;
	memset(&dokanOptions, 0, sizeof(DOKAN_OPTIONS));
	dokanOptions.Version = DOKAN_VERSION;
	dokanOptions.ThreadCount = 0; // default
	const auto mountPoint = std::wstring(1, driveLetter);
	dokanOptions.MountPoint = mountPoint.c_str();
	dokanOptions.Options = DOKAN_OPTION_REMOVABLE;
#if !defined(NDEBUG)
	dokanOptions.Options |= (DOKAN_OPTION_DEBUG | DOKAN_OPTION_STDERR);
#endif

	DOKAN_OPERATIONS dokanOperations;
	FillDokanOperations(dokanOperations);

	auto status = DokanMain(&dokanOptions, &dokanOperations);
	switch (status) {
	case DOKAN_SUCCESS:
		Log("Success");
		break;
	case DOKAN_ERROR:
		Log("Error");
		break;
	case DOKAN_DRIVE_LETTER_ERROR:
		Log("Bad Drive letter");
		break;
	case DOKAN_DRIVER_INSTALL_ERROR:
		Log("Can't install driver");
		break;
	case DOKAN_START_ERROR:
		Log("Driver something wrong");
		break;
	case DOKAN_MOUNT_ERROR:
		Log("Can't assign a drive letter");
		break;
	case DOKAN_MOUNT_POINT_ERROR:
		Log("Mount point error");
		break;
	case DOKAN_VERSION_ERROR:
		Log("Version error");
		break;
	default:
		Log("Unknown error: ", status);
		break;
	}
}
