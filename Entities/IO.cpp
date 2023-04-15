#include "IO.h"

IO::IO() : allocated(nullptr)
{
}


void IO::addToBlk(Process* blockedProcess)
{
	blkList.push(blockedProcess);
}


void IO::allocateIO()
{
	if (allocated)
		return;

	if (blkList.empty())
		return;	

	allocated = blkList.front();
	blkList.pop();
}


void IO::runIo()
{
	if (allocated)
		allocated->runIO();
}

bool IO::isBusy()
{
	if (allocated)
		return true;
	else
		return false;
}
