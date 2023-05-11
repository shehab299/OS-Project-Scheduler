#include "FCFSProcessor.h"

#include <string>

FCFSProcessor::FCFSProcessor(int id) : Processor(id)
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

	if (currentProcess->requestFork())
	{
		schedulerPtr->forkProcess(currentProcess);
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
		{
			killProcess = readyQueue.getElement(i);
			if(killProcess)
				readyQueue.remove(i);
			break;
		}
	}

	if (killProcess)
	{
		schedulerPtr->terminateProcess(killProcess);
	}
}



int FCFSProcessor::getProcessorType()
{
	return FCFS;
}

int FCFSProcessor::getProcessorLoad()
{
	return busyTime / schedulerPtr->getTotalTurnTime();
}

std::string FCFSProcessor::toString()
{
	std::string text = "processor " + std::to_string(processorId) + " [FCFS]: ";
	text += std::to_string(readyQueue.getSize()) + " " + "RDY: ";
	text += readyQueue.toString();
	return text;
}

bool FCFSProcessor::isReadyEmpty()
{
	return readyQueue.isEmpty();
}
Process* FCFSProcessor::stolenItem()
{
	Process* top=readyQueue.getElement(0);
	readyQueue.remove(0);
	return top;
}



