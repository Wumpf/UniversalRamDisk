#include "../UniversalRamDiskLib/UniversalRamDisk.h"
#include "../UniversalRamDiskLib/Mounting.h"

int main()
{
	// TODO: Command line interface
	UniversalRamDisk ramDisk;
	MountedDisk::MountDiskAndRun(ramDisk, L's');
	return 0;
}
