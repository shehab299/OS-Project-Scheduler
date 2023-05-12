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
		addProcess(currentProcess);
		currentProcess = nullptr;
	}
}

void RRProcessor::killProcess(KillSignal sig)
{
}

int RRProcessor::getProcessorType()
{
	return RR;
}



std::string RRProcessor::toString()
{
	string text = "processor " + to_string(processorId) + " [RR  ]: ";
	text += to_string(readyQueue.getSize()) + " " + "RDY: ";
	text += readyQueue.toString();
	return text;
}

int RRProcessor::getProcessorLoad()
{
	return busyTime / schedulerPtr->getTotalTurnTime();
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

	readyQueue.dequeue();
	expectedFinishTime -= top->getRemainingTime();

	return top;
}

void RRProcessor::removeFromReady(int id)
{
}

int RRProcessor::getFinishTime()
{
	if(readyQueue.isEmpty())
		return 0;
	return expectedFinishTime;
}

