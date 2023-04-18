#include "RRProcessor.h"


RRProcessor::RRProcessor(int timeSlice) : timeSlice(timeSlice), remainingTime(timeSlice)
{
}

void RRProcessor::addProcess(Process* process)
{
	if (process)
	{
		expectedFinishTime += process->getRemainingTime();
		readyQueue.enqueue(process);
	}
}


void RRProcessor::getNextProcess()
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

void RRProcessor::run()
{
	if (!currentProcess)
		getNextProcess();

	if (!currentProcess)
	{
		freeTime++;
		return;
	}

	// Check if the current process needs I/O
	if (currentProcess->needsIO())
	{
		schedulerPtr->blockProcess(currentProcess);
		currentProcess = nullptr;
		return;
	}

	// Run the current process

	if (!currentProcess->gotToCpu())
	{
		int RT = clk->getTime() - currentProcess->getArrivalTime();
		currentProcess->setResponseTime(RT);
		currentProcess->setFlag();
	}

	currentProcess->setState(RUN);
	currentProcess->run();


	busyTime++;
	remainingTime--;

	// Check if the process has finished
	if (currentProcess->isFinished())
	{
		schedulerPtr->terminateProcess(currentProcess);
		currentProcess = nullptr;
		remainingTime = timeSlice;
		return;
	}

	// End of the time slice and the process is not finished yet 
	if (remainingTime == 0)
	{
		remainingTime = timeSlice;
		currentProcess->setState(RDY);
		currentProcess = nullptr;
		readyQueue.rotate();
	}
}

void RRProcessor::DisplayReady()
{
	Process* cur;
	CircularQueue<Process*> temp;
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

void RRProcessor::killProcess(KillSignal sig)
{
}

int RRProcessor::getProcessorType()
{
	return RR;
}

bool RRProcessor::isProcessIn(int id)
{
	return false;
}
