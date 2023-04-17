#include "Scheduler.h"


#include <cstdlib>
#include <ctime>

int Scheduler::getMinProcessorIndex()
{
	int size = processorList.getSize();

	int minIndex = INT_MAX;
	int minTime = INT_MAX;
	for(int i = 0 ; i < size ; i++)
	{
		int time = processorList.getElement(i)->getFinishTime();
		if (time < minTime)
		{
			minIndex = i;
			minTime = time;
		}
	}
	return minIndex;
}

int Scheduler::generateRandomNumber()
{
	srand(time(0));
	int randomNumber = rand() % 100 + 1;
	return randomNumber;
}

Scheduler::Scheduler(int rtf, int maxW, int stl, int forkProp) :
	totalTurnaroundTime(0) , RR_RTF(rtf) , FCFS_MaxWait(maxW) 
	, forkProp(forkProp) , STL(stl) , clk(nullptr)
{
}

int Scheduler::getTotalTurnTime() const
{
	return totalTurnaroundTime;
}

void Scheduler::setClock(Clock* clkPtr)
{
	clk = clkPtr;
}

void Scheduler::setNProcesses(int n)
{
	nProcesses = n;
}

int Scheduler::getNProcesses()
{
	return nProcesses;
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

void Scheduler::scheduleProcess(Process* process)
{
	/* Phase 2
	int minIndex = getMinProcessorIndex();
	processorList.getElement(minIndex)->addProcess(process);
	*/

	static int nextProcessorIndex = 0;

	processorList.getElement(nextProcessorIndex)->addProcess(process);

	nextProcessorIndex++;
	nextProcessorIndex %= processorList.getSize();
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


void Scheduler::testRun()
{
	while (trmList.queueSize() != nProcesses)
	{
		while (!newList.isEmpty() && newList.peek()->getArrivalTime() == clk->getTime()) {
			scheduleProcess(newList.peek());
			newList.dequeue();
		}

		for (int i = 0; i < processorList.getSize(); i++)
		{
			Processor* processorPtr = processorList.getElement(i);

			processorPtr->testRun();

			int prop = generateRandomNumber();

			Process* runningProcess = nullptr;
			if (prop >= 1 && prop <= 15)
			{
				runningProcess = processorPtr->getRunningProcess();
				if (runningProcess)
					blockProcess(runningProcess);
			}
			else if (prop >= 20 && prop <= 30)
			{
				runningProcess = processorPtr->getRunningProcess();
				if (runningProcess)
					processorPtr->addProcess(runningProcess);
			}
			else if (prop >= 50 && prop <= 60)
			{
				runningProcess = processorPtr->getRunningProcess();
				if (runningProcess)
					terminateProcess(runningProcess);
			}


			if (processorPtr->getProcessorType() == FCFS)
			{
				int n = generateRandomNumber();
				while (!processorPtr->isProcessIn(n))
				{
					n = generateRandomNumber();
				}

				KillSignal newSig(n, clk->getTime());
				processorPtr->killProcess(newSig);
			}
		}

		int propIo = generateRandomNumber();

		if (propIo < 10)
		{
			if (ioHandler.isBusy())
				scheduleProcess(ioHandler.getAllocated());
		}

		clk->incrementTime();

	}
}

void Scheduler::run()
{
	while (!newList.isEmpty() && newList.peek()->getArrivalTime() == clk->getTime()) {
		scheduleProcess(newList.peek());
		newList.dequeue();
	}

	for (int i = 0; i < processorList.getSize(); i++)
	{
		processorList.getElement(i)->run();
	}

	clk->incrementTime();
}




