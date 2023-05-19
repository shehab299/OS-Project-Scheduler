#include "Scheduler.h"


#include <cstdlib>
#include <ctime>
#include <iomanip>


Scheduler::Scheduler(int nFcfs , int nRR , int nSJF , int stl) :
	totalTurnaroundTime(0) , STL(stl) , clk(nullptr) , nBusyProcessors(0) , nProcesses(0),
	numberFcfs(nFcfs) , numberSJF(nSJF) , numberRR(nRR) , totalWaitTime(0),
	totalResponseTime(0) , migrationMAXWcnt(0) , migrationRTFcnt(0) , stealCnt(0)
	, KillCnt(0) , forkCnt(0)
{
	ioHandler.setSchedulerPtr(this);
}

int Scheduler::getTotalTurnTime() const
{
	return totalTurnaroundTime;
}

double Scheduler::getStealProb()
{
	if (!nProcesses)
		return 0;

	return (double(stealCnt) /nProcesses) * 100;
}

double Scheduler::getMigrationtoRRProb()
{
	if (!nProcesses)
		return 0;

	return ( double(migrationMAXWcnt) / nProcesses) * 100;
}

double Scheduler::getMigrationtoSJFProb()
{
	if (!nProcesses)
		return 0;

	return ( double(migrationRTFcnt) / nProcesses) * 100;
}

double Scheduler::getForkProb()
{
	if (!nProcesses)
		return 0;

	return ( (double(forkCnt) / nProcesses) * 100);
}

double Scheduler::getKillProb()
{
	if (!nProcesses)
		return 0;

	return ( (double(KillCnt) / nProcesses) * 100);
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
		Processor*  processorPtr = processorList.getElement(i);

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

void Scheduler::updateStatistics(Process* processPtr)
{
	totalResponseTime += processPtr->getResponseTime();
	totalTurnaroundTime += processPtr->getTurnaroundTime();
	totalWaitTime += processPtr->getWaitingTime();
}

std::string Scheduler::getProcessSummary(Process* processPtr)
{
	std::stringstream output;
	output << std::setw(4) << processPtr->getTerminationTime() << " ";
	output << std::setw(4) << processPtr->getId() << " ";
	output << std::setw(4) << processPtr->getArrivalTime() << " ";
	output << std::setw(4) << processPtr->getTotalIoTime() << " ";
	output << std::setw(4) << processPtr->getWaitingTime() << " ";
	output << std::setw(4) << processPtr->getResponseTime() << " ";
	output << std::setw(4) << processPtr->getTurnaroundTime() << " ";
	output << '\n';
	return output.str();
}


void Scheduler::setClock(Clock* clkPtr)
{
	clk = clkPtr;
}

void Scheduler::setNProcesses(int nProcesses)
{
	this->nProcesses = nProcesses;
}

int Scheduler::getNumberSJF() const
{
	return numberSJF;
}

int Scheduler::getNumberRR() const
{
	return numberRR;
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


	updateStatistics(finishedProcess);
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
	}
	else {
		minIndex = getMinProcessorIndex();
	}

	process->setState(RDY);
	Processor* processorPtr = processorList.getElement(minIndex);

	processorPtr->addProcess(process);
}

void Scheduler::killProcess(KillSignal signal)
{
	int size = processorList.getSize();

	bool killed;

	for(int i = 0; i < size ; i++)
	{
		if (processorList.getElement(i)->getProcessorType() == FCFS)
		{
			killed = processorList.getElement(i)->killProcess(signal);
		}

		if (killed)
		{
			KillCnt++;
			break;
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
		forkCnt++;
		return;
	}
	else if (!process->getRightChild())
	{
		process->setRightChild(forked);
		scheduleProcess(forked, true);
		forkCnt++;
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

	if (clk->getTime() % STL == 0 && clk->getTime() != 0)
	{
		if(processorList.getSize()!=1)
		this->workStealing();
	}

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
		else if (processorPtr->getFinishTime() < shortest->getFinishTime())
			shortest = processorPtr;
	}

	double percent = calculateStealPercent(shortest, longest);

	while(percent > StealLimit) 
	{
		Process* processPtr = longest->getStolenItem();

		if (!processPtr)
			return;

		shortest->addProcess(processPtr);
		stealCnt++;
		percent = calculateStealPercent(shortest, longest);
	}
}

void Scheduler::migrateToRR(Process* process)
{
	if (!numberRR)
		return;

	int minIndex = getMinRRProcessorIndex();
	Processor* processorPtr = processorList.getElement(minIndex);
	process->setState(RDY);
	processorPtr->addProcess(process);
	migrationMAXWcnt++;
}

void Scheduler::migrateToSJF(Process* process)
{
	int minIndex = getMinSJFProcessorIndex();
	Processor* processorPtr = processorList.getElement(minIndex);
	process->setState(RDY);
	processorPtr->addProcess(process);
	migrationRTFcnt++;
}


std::string Scheduler::getStatistics()
{
	std::stringstream text;

	text << std::setw(4) << "TT" << " ";
	text << std::setw(4) << "PID" << " ";
	text << std::setw(4) << "AT" << " ";
	text << std::setw(4) << "IO_D" << " ";
	text << std::setw(4) << "WT" << " ";
	text << std::setw(4) << "RT" << " ";
	text << std::setw(4) << "TRT" << "\n";


	while(!trmList.isEmpty())
	{
		Process* toPrint = trmList.peek();
		trmList.dequeue();
		text << getProcessSummary(toPrint);
		delete toPrint;
	}

	text << endl << endl;
	text << "Processes: " << nProcesses << std::endl;

	text << "Avg WT = " << (totalWaitTime / nProcesses) << ", ";
	text << "Avg RT = " << (totalResponseTime / nProcesses) << ", ";
	text << "Avg TRT = " << (totalTurnaroundTime / nProcesses) << ", " << endl;


	text << "Migration : " << "RTF = " << getMigrationtoSJFProb() << " ";
	text << "MaxW = " << getMigrationtoRRProb() << endl;
	text << "Steal     : " << getStealProb() << endl;
	text << "Fork      : " << getForkProb() << endl;
	text << "Kill      : " << getKillProb() << endl;

	text << endl << endl;

	text << "Processors: " << processorList.getSize();
	text << " [ FCFS " << numberFcfs;
	text << " RR " << numberRR;
	text << " SJF " << numberSJF << " ]";
	text << endl;

	text << "Processor Load: " << endl;
	for (int i = 0; i < processorList.getSize(); i++)
	{
		Processor* processorPtr = processorList.getElement(i);

		text << "(p" << processorPtr->getId() << ") : " << processorPtr->getProcessorLoad() << "% ";

	}

	text << endl << endl;

	text << "Processor Utilization: " << endl;
	double totalUtil = 0;
	for (int i = 0; i < processorList.getSize(); i++)
	{
		Processor* processorPtr = processorList.getElement(i);

		int utilization = processorPtr->getUtilization();

		totalUtil += utilization;

		text << "(p" << processorPtr->getId() << ") : " << utilization << "%  ";
	}
	text << endl;

	text << "Avg Utilization : " << totalUtil / processorList.getSize() << "%";

	return text.str();
}

bool Scheduler::isFinished()
{
	return (nProcesses == trmList.getSize());
}
