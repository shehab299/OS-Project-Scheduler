#include "SJFProcessor.h"

void SJFProcessor::addProcess(Process* process)
{
	process->setResponseTime(clk->getTime() - process->getArrivalTime());
	readyQueue.enqueue(process);
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
	getNextProcess();
	while (currentProcess)
	{
		// Check if the process needs I/O during execution
		if (currentProcess->needsIO())
		{
			currentProcess->setState(BLK);
			//move to BLK List
			busy = false;
			getNextProcess();
			continue;
		}
		currentProcess->setState(RUN);
		currentProcess->setResponseTime(clk->getTime());
		currentProcess->run();
		busyTime++;

		if (currentProcess->isFinished())
		{
			currentProcess->setTerminationTime(clk->getTime());
			schedulerPtr->terminateProcess(currentProcess);
			finishTime = clk->getTime();
			currentProcess = nullptr;
			busy = false;
			getNextProcess();
		}
	}
}
