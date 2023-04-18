#pragma once

#include "Process.h"
#include "../Utils/DS/Queue.h"

class IO
{
private:
	Queue <Process*> blkList;
	Process* allocated;
public:
	IO();
	void addToBlk(Process* blockedProcess);
	void allocateIO();
	void runIo();
	void DisplayBlk();
	Process* getAllocated();
	bool isBusy();
};

