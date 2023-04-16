#include "RRProcessor.h"


RRProcessor::RRProcessor(int timeSlice) :timeSlice(timeSlice),remainingTime(timeSlice)
{
}

void RRProcessor::addProcess(Process* process)
{
	if (process)
	{
		expectedFinishTime += process->getRemainingTime();
		process->setResponseTime(clk->getTime() - process->getArrivalTime());
		readyQueue.enqueue(process);
	}
}


void RRProcessor::getNextProcess()
{
	if (!readyQueue.isEmpty())
	{
		currentProcess = readyQueue.peek();
		readyQueue.dequeue();
		busy = true;
	}
	else
	{
		currentProcess = nullptr;
		busy = false;
	}
}

void RRProcessor::run()
{
	if (!currentProcess)
	{
		return;
	}
	// Check if the current process needs I/O
	if (currentProcess->needsIO())
	{
		currentProcess->setState(BLK);
		return;
	}
	// Run the current process
	currentProcess->setState(RUN);
	currentProcess->run();
	busyTime++;
	remainingTime--;
	// Check if the process has finished
	if (currentProcess->isFinished())
	{
		schedulerPtr->terminateProcess(currentProcess);
		return;
	}
	// End of the time slice and the process is not finished yet 
	if (remainingTime == 0)
	{
		remainingTime = timeSlice;
		currentProcess->setState(RDY);
		readyQueue.rotate();
	}
}