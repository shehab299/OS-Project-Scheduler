#include "Scheduler.h"


#include <cstdlib>
#include <ctime>


Scheduler::Scheduler(int rtf, int maxW, int stl, int forkProp) :
	totalTurnaroundTime(0) , RR_RTF(rtf) , FCFS_MaxWait(maxW) 
	, forkProp(forkProp) , STL(stl) , clk(nullptr) , nBusyProcessors(0)
{
	ioHandler.setSchedulerPtr(this);
}

int Scheduler::getTotalTurnTime() const
{
	return totalTurnaroundTime;
}

int Scheduler::getMinProcessorIndex()
{
	int size = processorList.getSize();

	int minIndex = INT_MAX;
	int minTime = INT_MAX;
	for (int i = 0; i < size; i++)
	{
		Processor* processorPtr = processorList.getElement(i);
		
		if (processorPtr->isReadyEmpty() && !processorPtr->isBusy())
		{
			minIndex = i;
			break;
		}

		int time = processorPtr->getFinishTime();

		if (time < minTime)
		{
			minIndex = i;
			minTime = time;
		}
	}
	return minIndex;
}

int Scheduler::getMinFCFSProcessorIndex()
{
	int size = processorList.getSize();

	int minIndex = INT_MAX;
	int minTime = INT_MAX;
	for (int i = 0; i < size; i++)
	{
		Processor* processorPtr = processorList.getElement(i);

		if (processorPtr->getProcessorType() != FCFS)
			continue;

		if (processorPtr->isReadyEmpty() && !processorPtr->isBusy())
		{
			minIndex = i;
			break;
		}

		int time = processorPtr->getFinishTime();

		if (time < minTime)
		{
			minIndex = i;
			minTime = time;
		}
	}

	return minIndex;
}


void Scheduler::setClock(Clock* clkPtr)
{
	clk = clkPtr;
}

void Scheduler::setNProcesses(int nProcesses)
{
	this->nProcesses = nProcesses;
}

void Scheduler::addNewProcess(Process* newProcess)
{
	newProcess->setState(NEW);
	newList.enqueue(newProcess);
}

void Scheduler::addProcessor(Processor* Processor)
{
	int pos = processorList.getSize();
	processorList.insert(pos,Processor);
}

void Scheduler::addKillSignal(KillSignal signal)
{
	killList.enqueue(signal);
}

void Scheduler::blockProcess(Process* blockedProcess)
{
	blockedProcess->setState(BLK);
	ioHandler.addToBlk(blockedProcess);
}

void Scheduler::terminateProcess(Process* finishedProcess)
{
	finishedProcess->setState(TRM);
	finishedProcess->setTerminationTime(clk->getTime());
	totalTurnaroundTime += finishedProcess->getTurnaroundTime();
	trmList.enqueue(finishedProcess);
}

void Scheduler::scheduleProcess(Process* process , bool isForked)
{

	int minIndex;
	if (isForked)
		minIndex = getMinFCFSProcessorIndex();
	else
		minIndex = getMinProcessorIndex();

	Processor* processorPtr = processorList.getElement(minIndex);
	process->setState(RDY);
	processorPtr->addProcess(process);
}

void Scheduler::killProcess(KillSignal signal)
{
	int size = processorList.getSize();

	for(int i = 0; i < size ; i++)
	{
		if (processorList.getElement(i)->getProcessorType() == FCFS)
		{
			processorList.getElement(i)->killProcess(signal);
		}
	}

}

void Scheduler::forkProcess(Process* process)
{
	int id = ++nProcesses;
	int arrivalTime = clk->getTime();
	int cpuT = process->getRemainingTime();

	Process* forked = new Process(id, arrivalTime, cpuT);

	process->setChild(forked);

	scheduleProcess(forked, true);

}

std::string Scheduler::getIoInfo()
{
	return ioHandler.toString();
}

std::string Scheduler::getRunningInfo()
{
	int size = processorList.getSize();

	std::string text = " RUN: ";

	int nBusy = 0;

	for(int i = 0 ; i < size ; i++)
	{
		Processor* processorPtr = processorList.getElement(i);
		if (processorPtr->isBusy()) {
			nBusy++;
			text += std::to_string(processorPtr->getRunningId());
			text += "(P" + std::to_string(processorPtr->getId()) + ")";
			if (i != size - 1)
				text += ", ";
		}

	}
	text = std::to_string(nBusy) + text;
	return text;
}

std::string Scheduler::getTerminatedInfo()
{
	std::string text = std::to_string(trmList.getSize()) + " TRM: ";
	text += trmList.toString();
	return text;
}

std::string Scheduler::getProcessorsInfo()
{
	std::string text = "";

	int n = processorList.getSize();
	for(int i = 0 ; i < n ; i++)
	{
		text += processorList.getElement(i)->toString() + "\n";	
	}

	return text;
}


void Scheduler::run()
{
	while (!newList.isEmpty() && newList.peek()->getArrivalTime() == clk->getTime()) {
		scheduleProcess(newList.peek());
		newList.dequeue();
	}

	if(!killList.isEmpty())
		if (killList.peek().timeToKill == clk->getTime())
		{
			KillSignal sig = killList.peek();
			killList.dequeue();
			killProcess(sig);
		}


	for (int i = 0; i < processorList.getSize(); i++)
	{
		processorList.getElement(i)->run();
	}

	ioHandler.runIo();
}

int Scheduler::getNTerminated()
{
	return trmList.getSize();
}

bool Scheduler::calculateStealing(Processor* shorteset, Processor* longest)
{
	double val = (longest->getFinishTime() - shorteset->getFinishTime()) / double(longest->getFinishTime());
	return(val * 100 > STL);
}

void Scheduler::workStealing()
{
	Processor * shortest= processorList.getElement(0);
	Processor* longest = processorList.getElement(0);

	for (size_t i = 0; i < processorList.getSize(); i++)
	{
		if (processorList.getElement(i)->getFinishTime() > longest->getFinishTime())
			longest = processorList.getElement(i);
		else if(processorList.getElement(i)->getFinishTime()< shortest->getFinishTime())
			shortest = processorList.getElement(i);
	}
	while (calculateStealing(shortest, longest))
	{
		Process* p = longest->stolenItem();
		shortest->addProcess(p);
	}
}
