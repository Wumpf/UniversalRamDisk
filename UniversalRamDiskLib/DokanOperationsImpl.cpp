#include "dokan/dokan.h"
#include "Log.h"
#include "GlobalMountEvent.h"
#include "UniversalRamDisk.h"

#define ENABLE_CALL_REPORTS 0

#if ENABLE_CALL_REPORTS
	#define REPORT_CALL(...) do { LogCommaSeparated(__FUNCTION__, __VA_ARGS__); } while(false)
#else
	#define REPORT_CALL(...)
#endif

NTSTATUS DOKAN_CALLBACK URAMD_CreateFile(
	LPCWSTR FileName,
	PDOKAN_IO_SECURITY_CONTEXT SecurityContext,
	ACCESS_MASK DesiredAccess,
	ULONG FileAttributes,
	ULONG ShareAccess,
	ULONG CreateDisposition,
	ULONG CreateOptions,
	PDOKAN_FILE_INFO DokanFileInfo)
{
	REPORT_CALL(FileName);
	return STATUS_SUCCESS;
}

void DOKAN_CALLBACK URAMD_Cleanup(LPCWSTR FileName, PDOKAN_FILE_INFO DokanFileInfo)
{
	REPORT_CALL();
}

void DOKAN_CALLBACK URAMD_CloseFile(LPCWSTR FileName, PDOKAN_FILE_INFO DokanFileInfo)
{
	REPORT_CALL();
}

NTSTATUS DOKAN_CALLBACK URAMD_ReadFile(
	LPCWSTR FileName,
	LPVOID Buffer,
	DWORD BufferLength,
	LPDWORD ReadLength,
	LONGLONG Offset,
	PDOKAN_FILE_INFO DokanFileInfo)
{
	REPORT_CALL();
	return STATUS_SUCCESS;
}

NTSTATUS DOKAN_CALLBACK URAMD_WriteFile(
	LPCWSTR FileName,
	LPCVOID Buffer,
	DWORD NumberOfBytesToWrite,
	LPDWORD NumberOfBytesWritten,
	LONGLONG Offset,
	PDOKAN_FILE_INFO DokanFileInfo)
{
	REPORT_CALL();
	return STATUS_SUCCESS;
}

NTSTATUS DOKAN_CALLBACK URAMD_FlushFileBuffers(
	LPCWSTR FileName,
	PDOKAN_FILE_INFO DokanFileInfo)
{
	REPORT_CALL();
	return STATUS_SUCCESS;
}

NTSTATUS DOKAN_CALLBACK URAMD_GetFileInformation(
	LPCWSTR FileName,
	LPBY_HANDLE_FILE_INFORMATION Buffer,
	PDOKAN_FILE_INFO DokanFileInfo)
{
	REPORT_CALL();
	return STATUS_SUCCESS;
}

NTSTATUS DOKAN_CALLBACK URAMD_FindFiles(
	LPCWSTR FileName,
	PFillFindData FillFindData,
	PDOKAN_FILE_INFO DokanFileInfo)
{
	REPORT_CALL();
	return STATUS_SUCCESS;
}

NTSTATUS DOKAN_CALLBACK URAMD_FindFilesWithPattern(
	LPCWSTR PathName,
	LPCWSTR SearchPattern,
	PFillFindData FillFindData,
	PDOKAN_FILE_INFO DokanFileInfo)
{
	REPORT_CALL();
	return STATUS_SUCCESS;
}

NTSTATUS DOKAN_CALLBACK URAMD_SetFileAttributes(
	LPCWSTR FileName,
	DWORD FileAttributes,
	PDOKAN_FILE_INFO DokanFileInfo)
{
	REPORT_CALL();
	return STATUS_SUCCESS;
}

NTSTATUS DOKAN_CALLBACK URAMD_SetFileTime(
	LPCWSTR FileName,
	CONST FILETIME *CreationTime,
	CONST FILETIME *LastAccessTime,
	CONST FILETIME *LastWriteTime,
	PDOKAN_FILE_INFO DokanFileInfo)
{
	REPORT_CALL();
	return STATUS_SUCCESS;
}

NTSTATUS DOKAN_CALLBACK URAMD_DeleteFile(
	LPCWSTR FileName,
	PDOKAN_FILE_INFO DokanFileInfo)
{
	REPORT_CALL();
	return STATUS_SUCCESS;
}

NTSTATUS DOKAN_CALLBACK URAMD_DeleteDirectory(
	LPCWSTR FileName,
	PDOKAN_FILE_INFO DokanFileInfo)
{
	REPORT_CALL();
	return STATUS_SUCCESS;
}

NTSTATUS DOKAN_CALLBACK URAMD_MoveFile(
	LPCWSTR FileName,
	LPCWSTR NewFileName,
	BOOL ReplaceIfExisting,
	PDOKAN_FILE_INFO DokanFileInfo)
{
	REPORT_CALL();
	return STATUS_SUCCESS;
}

NTSTATUS DOKAN_CALLBACK URAMD_SetEndOfFile(
	LPCWSTR FileName,
	LONGLONG ByteOffset,
	PDOKAN_FILE_INFO DokanFileInfo)
{
	REPORT_CALL();
	return STATUS_SUCCESS;
}

NTSTATUS DOKAN_CALLBACK URAMD_SetAllocationSize(
	LPCWSTR FileName,
	LONGLONG AllocSize,
	PDOKAN_FILE_INFO DokanFileInfo)
{
	REPORT_CALL();
	return STATUS_SUCCESS;
}

NTSTATUS DOKAN_CALLBACK URAMD_LockFile(
	LPCWSTR FileName,
	LONGLONG ByteOffset,
	LONGLONG Length,
	PDOKAN_FILE_INFO DokanFileInfo)
{
	REPORT_CALL();
	return STATUS_SUCCESS;
}

NTSTATUS DOKAN_CALLBACK URAMD_UnlockFile(
	LPCWSTR FileName,
	LONGLONG ByteOffset,
	LONGLONG Length,
	PDOKAN_FILE_INFO DokanFileInfo)
{
	REPORT_CALL();
	return STATUS_SUCCESS;
}

NTSTATUS DOKAN_CALLBACK URAMD_GetDiskFreeSpace(PULONGLONG FreeBytesAvailable,
	PULONGLONG TotalNumberOfBytes,
	PULONGLONG TotalNumberOfFreeBytes,
	PDOKAN_FILE_INFO DokanFileInfo)
{
	REPORT_CALL();
	return STATUS_SUCCESS;
}

NTSTATUS DOKAN_CALLBACK URAMD_GetVolumeInformation(
	LPWSTR VolumeNameBuffer,
	DWORD VolumeNameSize,
	LPDWORD VolumeSerialNumber,
	LPDWORD MaximumComponentLength,
	LPDWORD FileSystemFlags,
	LPWSTR FileSystemNameBuffer,
	DWORD FileSystemNameSize,
	PDOKAN_FILE_INFO DokanFileInfo)
{
	REPORT_CALL();
	return STATUS_SUCCESS;
}

NTSTATUS DOKAN_CALLBACK URAMD_Mounted(PDOKAN_FILE_INFO DokanFileInfo)
{
	REPORT_CALL();
	g_mountEvent->SignalMounted();
	return STATUS_SUCCESS;
}

NTSTATUS DOKAN_CALLBACK URAMD_Unmounted(PDOKAN_FILE_INFO DokanFileInfo)
{
	REPORT_CALL();
	g_mountEvent->SignalUnmounted();
	return STATUS_SUCCESS;
}

NTSTATUS DOKAN_CALLBACK URAMD_GetFileSecurity(
	LPCWSTR FileName,
	PSECURITY_INFORMATION SecurityInformation,
	PSECURITY_DESCRIPTOR SecurityDescriptor,
	ULONG BufferLength,
	PULONG LengthNeeded,
	PDOKAN_FILE_INFO DokanFileInfo)
{
	REPORT_CALL();
	return STATUS_SUCCESS;
}

NTSTATUS DOKAN_CALLBACK URAMD_SetFileSecurity(
	LPCWSTR FileName,
	PSECURITY_INFORMATION SecurityInformation,
	PSECURITY_DESCRIPTOR SecurityDescriptor,
	ULONG BufferLength,
	PDOKAN_FILE_INFO DokanFileInfo)
{
	REPORT_CALL();
	return STATUS_SUCCESS;
}

NTSTATUS DOKAN_CALLBACK URAMD_FindStreams(
	LPCWSTR FileName,
	PFillFindStreamData FillFindStreamData,
	PDOKAN_FILE_INFO DokanFileInfo)
{
	REPORT_CALL();
	return STATUS_SUCCESS;
}
