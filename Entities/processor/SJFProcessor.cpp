#include "SJFProcessor.h"

void SJFProcessor::addProcess(Process* process)
{
	if (process)
	{
		expectedFinishTime += process->getRemainingTime();
		process->setResponseTime(clk->getTime() - process->getArrivalTime());
		readyQueue.enqueue(process);
	}
}

void SJFProcessor::getNextProcess()
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

void SJFProcessor::run()
{
	if (!currentProcess)
	{
		return;
	}

	// Check if the process needs I/O during execution
	if (currentProcess->needsIO())
	{
		currentProcess->setState(BLK);
		return;
	}

	// Run the the process
	currentProcess->setState(RUN);
	currentProcess->run();
	busyTime++;

	// Check if the process is finished
	if (currentProcess->isFinished())
	{
		schedulerPtr->terminateProcess(currentProcess);
	}
}
