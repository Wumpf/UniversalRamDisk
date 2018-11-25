#include "VRamDiskPlus.h"
#include "Log.h"
#include "GlobalMountEvent.h"

#include <string>
#include "dokan/dokan.h"

GlobalMountEvent* g_mountEvent = nullptr;

void FillDokanOperations(DOKAN_OPERATIONS& dokanOperations)
{
	NTSTATUS DOKAN_CALLBACK VRAMDP_CreateFile(LPCWSTR FileName, PDOKAN_IO_SECURITY_CONTEXT SecurityContext, ACCESS_MASK DesiredAccess, ULONG FileAttributes, ULONG ShareAccess, ULONG CreateDisposition, ULONG CreateOptions, PDOKAN_FILE_INFO DokanFileInfo);
	void DOKAN_CALLBACK VRAMDP_Cleanup(LPCWSTR FileName, PDOKAN_FILE_INFO DokanFileInfo);
	void DOKAN_CALLBACK VRAMDP_CloseFile(LPCWSTR FileName, PDOKAN_FILE_INFO DokanFileInfo);
	NTSTATUS DOKAN_CALLBACK VRAMDP_ReadFile(LPCWSTR FileName, LPVOID Buffer, DWORD BufferLength, LPDWORD ReadLength, LONGLONG Offset, PDOKAN_FILE_INFO DokanFileInfo);
	NTSTATUS DOKAN_CALLBACK VRAMDP_WriteFile(LPCWSTR FileName, LPCVOID Buffer, DWORD NumberOfBytesToWrite, LPDWORD NumberOfBytesWritten, LONGLONG Offset, PDOKAN_FILE_INFO DokanFileInfo);
	NTSTATUS DOKAN_CALLBACK VRAMDP_FlushFileBuffers(LPCWSTR FileName, PDOKAN_FILE_INFO DokanFileInfo);
	NTSTATUS DOKAN_CALLBACK VRAMDP_GetFileInformation(LPCWSTR FileName, LPBY_HANDLE_FILE_INFORMATION Buffer, PDOKAN_FILE_INFO DokanFileInfo);
	NTSTATUS DOKAN_CALLBACK VRAMDP_FindFiles(LPCWSTR FileName, PFillFindData FillFindData, PDOKAN_FILE_INFO DokanFileInfo);
	NTSTATUS DOKAN_CALLBACK VRAMDP_FindFilesWithPattern(LPCWSTR PathName, LPCWSTR SearchPattern, PFillFindData FillFindData, PDOKAN_FILE_INFO DokanFileInfo);
	NTSTATUS DOKAN_CALLBACK VRAMDP_SetFileAttributes(LPCWSTR FileName, DWORD FileAttributes, PDOKAN_FILE_INFO DokanFileInfo);
	NTSTATUS DOKAN_CALLBACK VRAMDP_SetFileTime(LPCWSTR FileName, CONST FILETIME *CreationTime, CONST FILETIME *LastAccessTime, CONST FILETIME *LastWriteTime, PDOKAN_FILE_INFO DokanFileInfo);
	NTSTATUS DOKAN_CALLBACK VRAMDP_DeleteFile(LPCWSTR FileName, PDOKAN_FILE_INFO DokanFileInfo);
	NTSTATUS DOKAN_CALLBACK VRAMDP_DeleteDirectory(LPCWSTR FileName, PDOKAN_FILE_INFO DokanFileInfo);
	NTSTATUS DOKAN_CALLBACK VRAMDP_MoveFile(LPCWSTR FileName, LPCWSTR NewFileName, BOOL ReplaceIfExisting, PDOKAN_FILE_INFO DokanFileInfo);
	NTSTATUS DOKAN_CALLBACK VRAMDP_SetEndOfFile(LPCWSTR FileName, LONGLONG ByteOffset, PDOKAN_FILE_INFO DokanFileInfo);
	NTSTATUS DOKAN_CALLBACK VRAMDP_SetAllocationSize(LPCWSTR FileName, LONGLONG AllocSize, PDOKAN_FILE_INFO DokanFileInfo);
	NTSTATUS DOKAN_CALLBACK VRAMDP_LockFile(LPCWSTR FileName, LONGLONG ByteOffset, LONGLONG Length, PDOKAN_FILE_INFO DokanFileInfo);
	NTSTATUS DOKAN_CALLBACK VRAMDP_UnlockFile(LPCWSTR FileName, LONGLONG ByteOffset, LONGLONG Length, PDOKAN_FILE_INFO DokanFileInfo);
	NTSTATUS DOKAN_CALLBACK VRAMDP_GetDiskFreeSpace(PULONGLONG FreeBytesAvailable, PULONGLONG TotalNumberOfBytes, PULONGLONG TotalNumberOfFreeBytes, PDOKAN_FILE_INFO DokanFileInfo);
	NTSTATUS DOKAN_CALLBACK VRAMDP_GetVolumeInformation(LPWSTR VolumeNameBuffer, DWORD VolumeNameSize, LPDWORD VolumeSerialNumber, LPDWORD MaximumComponentLength, LPDWORD FileSystemFlags, LPWSTR FileSystemNameBuffer, DWORD FileSystemNameSize, PDOKAN_FILE_INFO DokanFileInfo);
	NTSTATUS DOKAN_CALLBACK VRAMDP_Mounted(PDOKAN_FILE_INFO DokanFileInfo);
	NTSTATUS DOKAN_CALLBACK VRAMDP_Unmounted(PDOKAN_FILE_INFO DokanFileInfo);
	NTSTATUS DOKAN_CALLBACK VRAMDP_GetFileSecurity(LPCWSTR FileName, PSECURITY_INFORMATION SecurityInformation, PSECURITY_DESCRIPTOR SecurityDescriptor, ULONG BufferLength, PULONG LengthNeeded, PDOKAN_FILE_INFO DokanFileInfo);
	NTSTATUS DOKAN_CALLBACK VRAMDP_SetFileSecurity(LPCWSTR FileName, PSECURITY_INFORMATION SecurityInformation, PSECURITY_DESCRIPTOR SecurityDescriptor, ULONG BufferLength, PDOKAN_FILE_INFO DokanFileInfo);
	NTSTATUS DOKAN_CALLBACK VRAMDP_FindStreams(LPCWSTR FileName, PFillFindStreamData FillFindStreamData, PDOKAN_FILE_INFO DokanFileInfo);

	memset(&dokanOperations, 0, sizeof(DOKAN_OPTIONS));
	dokanOperations.ZwCreateFile = VRAMDP_CreateFile;
	dokanOperations.Cleanup = VRAMDP_Cleanup;
	dokanOperations.CloseFile = VRAMDP_CloseFile;
	dokanOperations.ReadFile = VRAMDP_ReadFile;
	dokanOperations.WriteFile = VRAMDP_WriteFile;
	dokanOperations.FlushFileBuffers = VRAMDP_FlushFileBuffers;
	dokanOperations.GetFileInformation = VRAMDP_GetFileInformation;
	dokanOperations.FindFiles = VRAMDP_FindFiles;
	dokanOperations.FindFilesWithPattern = VRAMDP_FindFilesWithPattern;
	dokanOperations.SetFileAttributes = VRAMDP_SetFileAttributes;
	dokanOperations.SetFileTime = VRAMDP_SetFileTime;
	dokanOperations.DeleteFile = VRAMDP_DeleteFile;
	dokanOperations.DeleteDirectory = VRAMDP_DeleteDirectory;
	dokanOperations.MoveFile = VRAMDP_MoveFile;
	dokanOperations.SetEndOfFile = VRAMDP_SetEndOfFile;
	dokanOperations.SetAllocationSize = VRAMDP_SetAllocationSize;
	dokanOperations.LockFile = VRAMDP_LockFile;
	dokanOperations.UnlockFile = VRAMDP_UnlockFile;
	dokanOperations.GetDiskFreeSpace = VRAMDP_GetDiskFreeSpace;
	dokanOperations.GetVolumeInformation = VRAMDP_GetVolumeInformation;
	dokanOperations.Mounted = VRAMDP_Mounted;
	dokanOperations.Unmounted = VRAMDP_Unmounted;
	dokanOperations.GetFileSecurity = VRAMDP_GetFileSecurity;
	dokanOperations.SetFileSecurity = VRAMDP_SetFileSecurity;
	dokanOperations.FindStreams = VRAMDP_FindStreams;
}

bool ValidateMountPointAndCreateEvent(wchar_t driveLetter)
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

	g_mountEvent = new GlobalMountEvent(driveLetter);
	return true;
}

void CreateDiskAndRun(wchar_t driveLetter)
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