#include "FCFSProcessor.h"
FCFSProcessor::FCFSProcessor()
{
}

int FCFSProcessor::getFinishTime()
{
	if (currentProcess)
	{
		return finishTime + currentProcess->getRemainingTime();
	}
	return finishTime;
}

void FCFSProcessor::addProcess(Process* process)
{
	readyQueue.insertEnd(process);
}

//kill process with passed id if found at passed timestep
void FCFSProcessor::killProcess(int processId, int sigKill)
{
	if (currentProcess && currentProcess->getId() == processId)
	{
		currentProcess->setTerminationTime(sigKill);
		//--->move the process to terminated list
		currentProcess = nullptr;
		return;
	}

	Node<Process*>* current = readyQueue.getHead();
	Node<Process*>* prev = nullptr;

	// Search for the process in the ready queue
	while (current)
	{
		if (current->getItem()->getId() == processId)
		{
			current->getItem()->setTerminationTime(sigKill);
			// --->Move the process to the terminated list

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

void FCFSProcessor::getNextProcess(int clock)
{
	if (!currentProcess && !readyQueue.isEmpty())
	{
		currentProcess = readyQueue.getHead()->getItem();
		readyQueue.deleteFirst();
		currentProcess->setState(RUN);
		currentProcess->setResponseTime(clock);
	}
}

void FCFSProcessor::run(int clock)
{
	if (currentProcess && !currentProcess->isFinished())
	{
		busyTime++;
		currentProcess->run();

		if (currentProcess->isFinished())
		{
			currentProcess->setTerminationTime(clock);
			currentProcess->setState(TRM);
			finishTime = clock;
			currentProcess = nullptr;
		}
	}
	else
		freeTime++;
 //clock++;
}

