#pragma once

#include <string>

class UniversalRamDisk;
class GlobalMountEvent;

// Static class for a mounted disk.
// (Per process there is only a single disk mount supported)
class MountedDisk
{
public:
	// Mounts the given ramdisk using Dokan.
	// Blocks until unmounted.
	static void MountDiskAndRun(UniversalRamDisk& ramDisk, wchar_t driveLetter);

	static inline std::wstring DriveLetterToRootPath(wchar_t driveLetter) { return std::wstring(1, driveLetter) + L":/"; }

	static UniversalRamDisk* GetDisk()			{ return m_ramDisk; }
	static GlobalMountEvent* GetMountEvent()	{ return m_mountEvent; }

private:
	MountedDisk() = delete;

	static bool ValidateMountPointAndCreateEvent(wchar_t driveLetter);

	static UniversalRamDisk* m_ramDisk;
	static GlobalMountEvent* m_mountEvent;
};