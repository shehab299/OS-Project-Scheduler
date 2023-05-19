#include "RRProcessor.h"


RRProcessor::RRProcessor(int id , int timeSlice) : 
	Processor(id), timeSlice(timeSlice), remainingTime(timeSlice)
{
}

void RRProcessor::addProcess(Process* process)
{
	if (process)
	{
		process->setProcessorId(processorId);
		expectedFinishTime += process->getRemainingTime();
		readyQueue.enqueue(process);
	}
}


void RRProcessor::getNextProcess()
{
	while (!readyQueue.isEmpty())
	{
		currentProcess = readyQueue.peek();
		readyQueue.dequeue();
		currentProcess->setWaitingTimeSoFar(clk->getTime());
		expectedFinishTime -= currentProcess->getRemainingTime();

		if (currentProcess->shouldMigrateToSFJ() && schedulerPtr->getNumberSJF())
		{
			schedulerPtr->migrateToSJF(currentProcess);
			continue;
		}

		remainingTime = timeSlice;
		return;
	}

	currentProcess = nullptr;
}

void RRProcessor::run()
{
	if (!currentProcess)
		getNextProcess();

	if (!currentProcess)
	{
		freeTime++;
		busy = false;
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

	busy = true;
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
		currentProcess->setState(RDY);
		addProcess(currentProcess);
		currentProcess = nullptr;
	}
}

bool RRProcessor::killProcess(KillSignal sig)
{
	return false;
}


int RRProcessor::getProcessorType()
{
	return RR;
}



std::string RRProcessor::toString()
{
	std::string text = "processor " + std::to_string(processorId) + " [RR  ]: ";
	text += std::to_string(readyQueue.getSize()) + " " + "RDY: ";
	text += readyQueue.toString();
	return text;
}

double RRProcessor::getProcessorLoad()
{
	return (double(busyTime) * 100) / schedulerPtr->getTotalTurnTime();
}

bool RRProcessor::isReadyEmpty()
{
	return readyQueue.isEmpty();
}

Process* RRProcessor::getStolenItem()
{
	if (readyQueue.isEmpty())
		return nullptr;

	Process* top = readyQueue.peek();

	if (top->isChild())
		return nullptr;

	readyQueue.dequeue();
	expectedFinishTime -= top->getRemainingTime();

	return top;
}

void RRProcessor::removeFromReady(int id)
{
	return;
}

int RRProcessor::getFinishTime()
{
	if(readyQueue.isEmpty())
		return 0;
	return expectedFinishTime;
}

