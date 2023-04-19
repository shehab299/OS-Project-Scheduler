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

std::string IO::toString()
{
	std::string text = std::to_string(blkList.getSize()) + " BLK: ";
	text += blkList.toString();
	return text;
}

Process* IO::getAllocated()
{
	Process* temp = allocated;
	allocated = nullptr;
	allocateIO();
	return temp;
}

bool IO::isBusy()
{
	if (allocated)
		return true;
	else
		return false;
}




