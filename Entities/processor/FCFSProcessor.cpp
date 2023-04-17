#include "FCFSProcessor.h"


FCFSProcessor::FCFSProcessor()
{
}


void FCFSProcessor::addProcess(Process* process)
{
	if (process)
	{
		expectedFinishTime += process->getRemainingTime();
		int pos = readyQueue.getSize();
		readyQueue.insert(pos, process);
	}
}

//Get the next process from the ready queue
void FCFSProcessor::getNextProcess()
{
	if (!readyQueue.isEmpty())
	{
		currentProcess = readyQueue.getElement(0);
		readyQueue.remove(0);
		expectedFinishTime -= currentProcess->getRemainingTime();
		busy = true;
	}
	else
	{
		freeTime++;
		currentProcess = nullptr;
		busy = false;
	}
}

void FCFSProcessor::run()
{

	if (!currentProcess)
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


void FCFSProcessor::killProcess(KillSignal sigkill)
{
	int killID = sigkill.processId;

	int size = readyQueue.getSize();

	Process* killProcess = nullptr;

	for(int i = 0 ; i < size ; i++)
	{
		if (readyQueue.getElement(i)->getId() == killID)
			killProcess = readyQueue.getElement(i);
	}

	if (killProcess)
	{
		schedulerPtr->terminateProcess(killProcess);
	}
}

bool FCFSProcessor::isProcessIn(int id)
{
	int n = readyQueue.getSize();

	for (int i = 0; i < n; i++)
	{
		if (readyQueue.getElement(i)->getId() == id)
			return true;
	}
	return false;
}

int FCFSProcessor::getProcessorType()
{
	return FCFS;
}


