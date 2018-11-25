#include "gtest/gtest.h"
#include <Windows.h>

#include "../UniversalRamDiskLib/UniversalRamDisk.h"
#include "../UniversalRamDiskLib/GlobalMountEvent.h"

class CommandLineTests : public ::testing::Test
{
protected:
	static void SetUpTestCase()
	{
		memset(&s_processInformation, 0, sizeof(s_processInformation));

		STARTUPINFO startupInfo;
		memset(&startupInfo, 0, sizeof(startupInfo));
		startupInfo.cb = sizeof(startupInfo);

		wchar_t commandLine[] = L"UniversalRamDisk.exe";
		BOOL result = CreateProcess(nullptr, commandLine, nullptr, nullptr, FALSE, CREATE_NEW_CONSOLE | CREATE_NEW_PROCESS_GROUP, nullptr, nullptr, &startupInfo, &s_processInformation);
		if (!result)
			printf("CreateProcess failed (%d).\n", GetLastError());
		ASSERT_TRUE(result);

		GlobalMountEvent mountEvent(s_driveLetter);
		mountEvent.WaitForMounted();
	}

	static void TearDownTestCase()
	{
		if (!s_processInformation.dwProcessId)
			return;

		TerminateProcess(s_processInformation.hProcess, 0);
		WaitForSingleObject(s_processInformation.hProcess, INFINITE);

		auto rootPath = DriveLetterToRootPath(s_driveLetter);
		EXPECT_EQ(GetDriveType(rootPath.c_str()), DRIVE_NO_ROOT_DIR);
	}

	static const wchar_t s_driveLetter = L's';

private:
	static PROCESS_INFORMATION s_processInformation;
};
PROCESS_INFORMATION CommandLineTests::s_processInformation;

TEST_F(CommandLineTests, DriveIsMounted)
{
	auto rootPath = DriveLetterToRootPath(s_driveLetter);
	EXPECT_EQ(GetDriveType(rootPath.c_str()), DRIVE_REMOVABLE);
}