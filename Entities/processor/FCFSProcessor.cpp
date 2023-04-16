#include "FCFSProcessor.h"
#include "FCFSProcessor.h"
FCFSProcessor::FCFSProcessor()
{
}


void FCFSProcessor::addProcess(Process* process)
{
	process->setResponseTime(clk->getTime() - process->getArrivalTime());
	readyQueue.insertEnd(process);
}

//Get the next process from the ready queue
void FCFSProcessor::getNextProcess()
{
	if (!readyQueue.isEmpty())
	{
		currentProcess = readyQueue.getHead()->getItem();
		readyQueue.deleteFirst();
		busy = true;
	}
	else
	{
		currentProcess = nullptr;
		busy = false;
	}
}

void FCFSProcessor::run()
{
	getNextProcess();
	while (currentProcess)
	{
		// Check if the process needs I/O during execution
		if (currentProcess->needsIO())
		{
			currentProcess->setState(BLK); //move to BLK List
			getNextProcess();
			busy = false;
			continue;
		}
		currentProcess->setState(RUN);
		currentProcess->run();
		busyTime++;

		if (currentProcess->isFinished())
		{
			currentProcess->setTerminationTime(clk->getTime());
			schedulerPtr->terminateProcess(currentProcess);
			finishTime = clk->getTime();
			currentProcess = nullptr;
			getNextProcess();
		}
	}
}
//kill process with passed id if found at passed timestep
void FCFSProcessor::killProcess(KillSignal sigkill)
{
	if (currentProcess && currentProcess->getId() == sigkill.processId)
	{
		currentProcess->setTerminationTime(sigkill.timeToKill);
		schedulerPtr->terminateProcess(currentProcess);
		currentProcess = nullptr;
		return;
	}

	Node<Process*>* current = readyQueue.getHead();
	Node<Process*>* prev = nullptr;

	// Search for the process in the ready queue
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