#include "SJFProcessor.h"

void SJFProcessor::addProcess(Process* process)
{
	if (process)
	{
		expectedFinishTime += process->getRemainingTime();
		readyQueue.enqueue(process);
	}
}

void SJFProcessor::getNextProcess()
{
	if (!readyQueue.isEmpty())
	{
		currentProcess = readyQueue.peek();
		readyQueue.dequeue();
		expectedFinishTime -= currentProcess->getRemainingTime();
		busy = true;
	}
	else
	{
		currentProcess = nullptr;
		busy = false;
	}
}

void SJFProcessor::killProcess(KillSignal signal)
{
}

int SJFProcessor::getProcessorType()
{
	return SJF;
}

bool SJFProcessor::isProcessIn(int id)
{
	return false;
}

void SJFProcessor::run()
{

	if(!currentProcess)
		getNextProcess();

	if (!currentProcess)
	{
		freeTime++;
		return;
	}

	// Check if the process needs I/O during execution
	if (currentProcess->needsIO())
	{
		schedulerPtr->blockProcess(currentProcess);
		currentProcess = nullptr;
		return;
	}


	if (!currentProcess->gotToCpu())
	{
		int RT = clk->getTime() - currentProcess->getArrivalTime();
		currentProcess->setResponseTime(RT);
		currentProcess->setFlag();
	}

	// Run the the process
	currentProcess->setState(RUN);
	currentProcess->run();
	busyTime++;

	// Check if the process is finished
	if (currentProcess->isFinished())
	{
		schedulerPtr->terminateProcess(currentProcess);
		currentProcess = nullptr;
		return;
	}
}

void SJFProcessor::DisplayReady()
{
	Process* cur;
	PriorityQueue<Process*> temp;
	while (!readyQueue.isEmpty())
	{
		cur = readyQueue.peek();
		temp.enqueue(cur);
		cout << cur->getId() << ", ";
		readyQueue.dequeue();
	}
	cout << endl;
	while (!temp.isEmpty())
	{
		readyQueue.enqueue(temp.peek());
		temp.dequeue();
	}
}
