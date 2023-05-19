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

double Processor::getUtilization()
{
    return (double(busyTime) / (busyTime + freeTime)) * 100;
}


void Processor::setClk(Clock* clkptr)
{
	clk = clkptr;
}




int Processor::getRunningId()
{
	return currentProcess->getId();
}

