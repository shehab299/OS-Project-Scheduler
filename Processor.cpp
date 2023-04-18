#include "Processor.h"

Processor::Processor() :busy(false), busyTime(0), freeTime(0), expectedFinishTime(0), currentProcess(nullptr), clk(nullptr),schedulerPtr(nullptr)
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

bool Processor::isBusy()
{
    return busy;
}

int Processor::getUtilization()
{
    return (busyTime / (busyTime + freeTime));
}

Process* Processor::getRunningProcess()
{
	Process* temp = currentProcess;
	currentProcess = nullptr;
	return temp;
}

void Processor::testRun()
{
	if (!currentProcess)
		getNextProcess();

	if (!currentProcess)
	{
		freeTime++;
		return;
	}

	busyTime++;
}
