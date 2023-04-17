#include "FCFSProcessor.h"


FCFSProcessor::FCFSProcessor()
{
}


void FCFSProcessor::addProcess(Process* process)
{
	if (process)
	{
		expectedFinishTime += process->getRemainingTime();
		process->setResponseTime(clk->getTime() - process->getArrivalTime());
		readyQueue.insertEnd(process);
	}
}

//Get the next process from the ready queue
void FCFSProcessor::getNextProcess()
{
	if (!readyQueue.isEmpty())
	{
		currentProcess = readyQueue.getHead()->getItem();
		readyQueue.deleteFirst();
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
	{
		return;
	}
	// Check if the process needs I/O
	if (currentProcess->needsIO())
	{
		currentProcess->setState(BLK);
		return;
	}
	// Run the process
	currentProcess->setState(RUN);
	currentProcess->run();
	busyTime++;

	// Check if the process is finished
	if (currentProcess->isFinished())
	{
		schedulerPtr->terminateProcess(currentProcess);
	}
}

//kill process with passed id if found at passed timestep
void FCFSProcessor::killProcess(KillSignal sigkill)
{
	// Check if the process to be killed is the current procces
	if (currentProcess && currentProcess->getId() == sigkill.processId)
	{
		currentProcess->setTerminationTime(sigkill.timeToKill);
		schedulerPtr->terminateProcess(currentProcess);
		currentProcess = nullptr;
		return;
	}

	// Search for the process in the ready queue
	//edit data structure 
	Node<Process*>* current = readyQueue.getHead();
	Node<Process*>* prev = nullptr;
	while (current)
	{
		if (current->getItem()->getId() == sigkill.processId)
		{
			current->getItem()->setTerminationTime(sigkill.timeToKill);
			schedulerPtr->terminateProcess(currentProcess);

			// Remove the process from the ready queue
			if (prev)
			{
				prev->setNext(current->getNext());
			}
			else
			{
				readyQueue.setHead(current->getNext());
			}
			return;
		}
		prev = current;
		current = current->getNext();
	}
}