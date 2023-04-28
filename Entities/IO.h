#pragma once

#include "Process.h"
#include "../Utils/DS/Queue.h"

class Scheduler;

class IO
{
private:
	Queue <Process*> blkList;
	Process* allocated;
	Scheduler* schedulerPtr;
public:
	IO();
	void addToBlk(Process* blockedProcess);
	void setSchedulerPtr(Scheduler* schedulerPtr);
	void allocateIO();
	void runIo();
	std::string toString();
	Process* getAllocated();
	bool isBusy();
};

