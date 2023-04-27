#include "IO.h"

my_IO::my_IO() : allocated(nullptr)
{
	cout << "aaaaaaaaaaa";
}


void my_IO::addToBlk(Process* blockedProcess)
{
	blkList.enqueue(blockedProcess);
}


void my_IO::allocateIO()
{
	if (allocated)
		return;

	if (blkList.isEmpty())
		return;	

	allocated = blkList.peek();
	blkList.dequeue();
}


void my_IO::runIo()
{
	if (!allocated)
		allocateIO();
}

std::string my_IO::toString()
{
	std::string text = std::to_string(blkList.getSize()) + " BLK: ";
	text += blkList.toString();
	return text;
}

Process* my_IO::getAllocated()
{
	Process* temp = allocated;
	allocated = nullptr;
	return temp;
}

bool my_IO::isBusy()
{
	if (allocated)
		return true;
	else
		return false;
}




