#include "IO.h"
#include "../Control/Scheduler.h"


IO::IO() : allocated(nullptr) , schedulerPtr(nullptr)
{
}


void IO::addToBlk(Process* blockedProcess)
{
	blkList.enqueue(blockedProcess);
}

void IO::setSchedulerPtr(Scheduler* schedulerPtr)
{
	this->schedulerPtr = schedulerPtr;
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

	if (!allocated)
		return;

	allocated->runIO();

	if (allocated->getIoTime() <= 0)
	{
		schedulerPtr->scheduleProcess(allocated);
		allocated = nullptr;
	}

}

std::string IO::toString()
{
	int size = blkList.getSize();
	if (allocated)
		size++;

	std::string text = std::to_string(size) + " BLK: ";
	if (allocated)
		text += "(" + to_string(allocated) + ") ";

	text += blkList.toString();

	return text;
}

Process* IO::getAllocated()
{
	Process* temp = allocated;
	allocated = nullptr;
	return temp;
}

bool IO::isBusy()
{
	if (allocated)
		return true;
	else
		return false;
}




