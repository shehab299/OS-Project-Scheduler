#include "SJFProcessor.h"

SJFProcessor::SJFProcessor(int id) : Processor(id)
{
}

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


std::string SJFProcessor::toString()
{
	string text = "processor " + to_string(processorId) + " [SJF ]: ";
	text += to_string(readyQueue.getSize()) + " " + "RDY: ";
	text += readyQueue.toString();
	return text;
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
