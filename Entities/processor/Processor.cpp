#include "Processor.h"


Processor::Processor(int id) :
	busy(false), busyTime(0), freeTime(0), expectedFinishTime(0), 
	currentProcess(nullptr), clk(nullptr),schedulerPtr(nullptr) , processorId(id)
{
}

void Processor::setSchedulerPtr(Scheduler* scheduler)
{
    schedulerPtr = scheduler;
}

int Processor::getFinishTime()
{
	return expectedFinishTime;
}

int Processor::getId()
{
	return processorId;
}

bool Processor::isBusy()
{
	if(currentProcess)
		return true;
	return false;
}

int Processor::getUtilization()
{
    return (busyTime / (busyTime + freeTime));
}


void Processor::setClk(Clock* clkptr)
{
	clk = clkptr;
}

int Processor::getRunningId()
{
	return currentProcess->getId();
}

