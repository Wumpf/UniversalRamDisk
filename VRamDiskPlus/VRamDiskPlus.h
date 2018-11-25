#pragma once

#include <string>

void CreateDiskAndRun(wchar_t driveLetter);

inline std::wstring DriveLetterToRootPath(wchar_t driveLetter) { return std::wstring(1, driveLetter) + L":/"; }

extern class GlobalMountEvent* g_mountEvent;
