#include "SJFProcessor.h"

SJFProcessor::SJFProcessor(int id) : Processor(id)
{
}

void SJFProcessor::addProcess(Process* process)
{
	if (process)
	{
		process->setProcessorId(processorId);
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
		currentProcess->setWaitingTimeSoFar(clk->getTime());
		expectedFinishTime -= currentProcess->getRemainingTime();
		return;
	}
	
	currentProcess = nullptr;
}

bool SJFProcessor::killProcess(KillSignal signal)
{
	return false;
}

int SJFProcessor::getProcessorType()
{
	return SJF;
}

bool SJFProcessor::isProcessIn(int id)
{
	return false;
}


std::string SJFProcessor::toString()
{
	string text = "processor " + to_string(processorId) + " [SJF ]: ";
	text += to_string(readyQueue.getSize()) + " " + "RDY: ";
	text += readyQueue.toString();
	return text;
}

double SJFProcessor::getProcessorLoad()
{
	return (double(busyTime) * 100) / schedulerPtr->getTotalTurnTime();
}

bool SJFProcessor::isReadyEmpty()
{
	return readyQueue.isEmpty();
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

Process* SJFProcessor::getStolenItem()
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

void SJFProcessor::removeFromReady(int id)
{
}


int SJFProcessor::getFinishTime()
{
	if (readyQueue.isEmpty())
		return 0;
	return expectedFinishTime;
}
