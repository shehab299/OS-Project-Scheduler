#include "FCFSProcessor.h"

#include <string>

FCFSProcessor::FCFSProcessor(int id) : Processor(id)
{
}


void FCFSProcessor::addProcess(Process* process)
{
	if (process)
	{
		process->setProcessorId(processorId);
		expectedFinishTime += process->getRemainingTime();
		int pos = readyQueue.getSize();
		readyQueue.insert(pos, process);
	}
}

//Get the next process from the ready queue
void FCFSProcessor::getNextProcess()
{
	while (!readyQueue.isEmpty())
	{
		currentProcess = readyQueue.getElement(0);
		readyQueue.remove(0);
		expectedFinishTime -= currentProcess->getRemainingTime();

		currentProcess->setWaitingTimeSoFar(clk->getTime());

		if (currentProcess->shouldMigrateToRR() && schedulerPtr->getNumberRR())
		{
			schedulerPtr->migrateToRR(currentProcess);
			continue;
		}
		else
			return;
	}

	currentProcess = nullptr;
}

void FCFSProcessor::run()
{

	if (!currentProcess)
		getNextProcess();

	if (!currentProcess)
	{
		freeTime++;
		busy = false;
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

	// Run the current process
	busy = true;
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

bool FCFSProcessor::killProcess(KillSignal sigkill)
{
	int killID = sigkill.processId;

	Process* killProcess = nullptr;

	int pos;

	killProcess = readyQueue.searchById(killID, pos);

	if (pos != -1)
	{
		readyQueue.remove(pos);
		expectedFinishTime -= killProcess->getRemainingTime();
		schedulerPtr->terminateProcess(killProcess);
		return true;
	}
	else
	{
		if (!currentProcess)
			return false;

		if (currentProcess->getId() == killID) {
			schedulerPtr->terminateProcess(currentProcess);
			currentProcess = nullptr;
			return true;
		}
	}


	return false;
}

void FCFSProcessor::removeFromReady(int id)
{
	int pos;
	Process* process = readyQueue.searchById(id, pos);

	if (pos != -1) {
		schedulerPtr->terminateProcess(process);
		expectedFinishTime -= process->getRemainingTime();
		readyQueue.remove(pos);
	}
	else
	{
		if (!currentProcess)
			return;

		if (currentProcess->getId() == id)
		{
			schedulerPtr->terminateProcess(currentProcess);
			currentProcess = nullptr;
		}
	}
}




int FCFSProcessor::getProcessorType()
{
	return FCFS;
}

double FCFSProcessor::getProcessorLoad()
{
	return (double(busyTime) * 100) / schedulerPtr->getTotalTurnTime();
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
Process* FCFSProcessor::getStolenItem()
{
	if (readyQueue.isEmpty())
		return nullptr;

	Process* top = readyQueue.getElement(0);

	if (top->isChild())
		return nullptr;

	readyQueue.remove(0);
	expectedFinishTime -= top->getRemainingTime();

	return top;
}

int FCFSProcessor::getFinishTime()
{
	return expectedFinishTime;
}



