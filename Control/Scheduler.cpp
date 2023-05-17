#include "Scheduler.h"


#include <cstdlib>
#include <ctime>


Scheduler::Scheduler(int rtf, int maxW, int stl, int forkProp) :
	totalTurnaroundTime(0) , RR_RTF(rtf) , FCFS_MaxWait(maxW) 
	, forkProp(forkProp) , STL(stl) , clk(nullptr) , nBusyProcessors(0) , nProcesses(0)
{
	ioHandler.setSchedulerPtr(this);
}

int Scheduler::getTotalTurnTime() const
{
	return totalTurnaroundTime;
}

double Scheduler::getStealingRatio()
{
	return (double(totalSteal)/nProcesses)*100;
}

double Scheduler::getMigrationtoRR()
{
	return (double(totalMax) / nProcesses) * 100;
}

double Scheduler::getMigrationtoSJF()
{
	return (double(totalRt) / nProcesses) * 100;
}

double Scheduler::getFork()
{
	return ((double(totalFork) / nProcesses) * 100);
}

double Scheduler::getKill()
{
	return ((double(totalKill) / nProcesses) * 100);
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

int Scheduler::getMinRRProcessorIndex()
{
	int size = processorList.getSize();

	int minIndex = INT_MAX;
	int minTime = INT_MAX;
	for (int i = 0; i < size; i++)
	{
		Processor* processorPtr = processorList.getElement(i);

		if (processorPtr->getProcessorType() != RR)
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

int Scheduler::getMinSJFProcessorIndex()
{
	int size = processorList.getSize();

	int minIndex = INT_MAX;
	int minTime = INT_MAX;
	for (int i = 0; i < size; i++)
	{
		Processor* processorPtr = processorList.getElement(i);

		if (processorPtr->getProcessorType() != SJF)
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
	blockedProcess->setProcessorId(-1);
	ioHandler.addToBlk(blockedProcess);
}

void Scheduler::terminateProcess(Process* finishedProcess)
{
	finishedProcess->setState(TRM);
	finishedProcess->setTerminationTime(clk->getTime());

	terminateChildren(finishedProcess);

	totalTurnaroundTime += finishedProcess->getTurnaroundTime();
	trmList.enqueue(finishedProcess);
}

void Scheduler::terminateChildren(Process* process)
{
	Process* left = process->getLeftChild();
	Process* right = process->getRightChild();

	if (left)
	{
		removeFromReady(left);
		process->setLeftChild(nullptr);
	}
	
	if (right)
	{
		removeFromReady(right);
		process->setRightChild(nullptr);
	}

}

void Scheduler::scheduleProcess(Process* process , bool isForked)
{

	int minIndex;
	if (isForked) {
		minIndex = getMinFCFSProcessorIndex();
		cout << "Forked " << process->getId() << endl;
	}
	else {
		minIndex = getMinProcessorIndex();
		cout << "ADDED " << process->getId() << endl;
	}
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

	Process* forked = new Process(id, arrivalTime, cpuT , true);

	if (!process->getLeftChild()) 
	{
		process->setLeftChild(forked);
		scheduleProcess(forked, true);
		cout << process->getId() << " Forked " << forked->getId() << endl;
		return;
	}
	else if (!process->getRightChild())
	{
		process->setRightChild(forked);
		scheduleProcess(forked, true);
		cout << process->getId() << " Forked " << forked->getId() << endl;
		return;
	}

	delete forked;
}

void Scheduler::removeFromReady(Process* process)
{
	Processor* fcfsProcessor = processorList.getElement(process->getProcessorLocation());
	fcfsProcessor->removeFromReady(process->getId());
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

	this->workStealing();

	while (!newList.isEmpty() && newList.peek()->getArrivalTime() == clk->getTime()) {
		scheduleProcess(newList.peek());
		newList.dequeue();
	}

	while (!killList.isEmpty() && killList.peek().timeToKill == clk->getTime())
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

double Scheduler::calculateStealPercent(Processor* shorteset, Processor* longest)
{
	int diff = (longest->getFinishTime() - shorteset->getFinishTime());
	
	if (diff <= 0)
		return 0;

	double percentage =  (diff / longest->getFinishTime()) * 100;
	return (percentage);
}

void Scheduler::workStealing()
{
	Processor* shortest;
	Processor* longest;

	shortest = longest = processorList.getElement(0);

	for (size_t i = 0; i < processorList.getSize(); i++)
	{
		Processor* processorPtr = processorList.getElement(i);

		if (processorPtr->getFinishTime() > longest->getFinishTime())
			longest = processorPtr;
		if (processorPtr->getFinishTime() < shortest->getFinishTime())
			shortest = processorPtr;
	}


	double percent = calculateStealPercent(shortest, longest);

	while(percent > StealLimit) 
	{
		Process* processPtr = longest->getStolenItem();
		cout << "Stole " << to_string(processPtr) << " from " << longest->getId() << "to" << shortest->getId() << endl;
		shortest->addProcess(processPtr);
		percent = calculateStealPercent(shortest, longest);
	}
}

void Scheduler::migrateToRR(Process* process)
{
	int minIndex = getMinRRProcessorIndex();
	Processor* processorPtr = processorList.getElement(minIndex);
	process->setState(RDY);
	processorPtr->addProcess(process);
}

void Scheduler::migrateToSJF(Process* process)
{
	int minIndex = getMinSJFProcessorIndex();
	Processor* processorPtr = processorList.getElement(minIndex);
	process->setState(RDY);
	processorPtr->addProcess(process);
}
std::string Scheduler::forOutputFile()
{
	std::string line = "TT  PID  AT  IO_D  WT  RT  TRT \n";
	//for process
	for (int i = 0 ; i < trmList.getSize() ; i++)
	{
		line += trmList.toString2();
	}
	line += "Processes: " + std::to_string(this->nProcesses)+ "\n";
	line += "Avg WT = " +
	line += "Migration %:     RTF= " + std::to_string(this->getMigrationtoSJF()) + "%,          MaxW = " + std::to_string(this->getMigrationtoRR()) + "\n";
	line += "Work Steal %: " + std::to_string(this->getMigrationtoSJF()) + "%" + "\n";
	line += "Forked Process %: " + std::to_string(this->getFork()) + "%" + "\n";
	line += "Killed Process %: " + std::to_string(this->getKill()) + "%" + "\n\n\n";


	line += "Processors: " + std::to_string(this->totalFCFS + this->totalRR + this->totalSJF) + " [ " + std::to_string(this->totalFCFS) + " FCFS, " + std::to_string(this->totalSJF) + " SJF, " + std::to_string(this->totalRR) + " RR]" + "\n";
	line += "Processors Load \n";
	for (int i = 0; i < processorList.getSize(); i++)
	{
		if(i!= processorList.getSize()-1)
		line += "p"+ std::to_string(i+1)+"="+ std::to_string((processorList.getElement(i))->getProcessorLoad())+"%, ";
		else
		line += "p" + std::to_string(i + 1) + "=" + std::to_string((processorList.getElement(i))->getProcessorLoad()) + "%\n ";
	}

	for (int i = 0; i < processorList.getSize(); i++)
	{
		if (i != processorList.getSize() - 1)
			line += "p" + std::to_string(i + 1) + "=" + std::to_string((processorList.getElement(i))->getUtilization()) + "%, ";
		else
			line += "p" + std::to_string(i + 1) + "=" + std::to_string((processorList.getElement(i))->getUtilization()) + "%\n ";
	}
	
	return line;
}
