#include "Processor.h"

Processor::Processor() :busy(false), busyTime(0), freeTime(0), finishTime(0), currentProcess(nullptr), clk(nullptr),schedulerPtr(nullptr)
{

}

void Processor::setSchedulerPtr(Scheduler* scheduler)
{
    schedulerPtr = scheduler;
}

int Processor::getFinishTime()
{
	if (currentProcess)
	{
		return finishTime + currentProcess->getRemainingTime();
	}
	return finishTime;
}

bool Processor::isBusy()
{
    return busy;
}

int Processor::getUtilization()
{
    return (busyTime / (busyTime + freeTime));
}
