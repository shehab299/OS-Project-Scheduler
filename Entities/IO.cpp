#include "IO.h"

IO::IO() : allocated(nullptr)
{
}


void IO::addToBlk(Process* blockedProcess)
{
	blkList.enqueue(blockedProcess);
}


void IO::allocateIO()
{
	if (allocated)
		return;

	if (blkList.isEmpty())
		return;	

	allocated = blkList.peek();
	blkList.dequeue();
}


void IO::runIo()
{
	if (!allocated)
		allocateIO();

	if (allocated)
		allocated->runIO();
}

Process* IO::getAllocated()
{
	return allocated;
}

bool IO::isBusy()
{
	if (allocated)
		return true;
	else
		return false;
}
