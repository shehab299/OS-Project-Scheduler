#include "Scheduler.h"

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

void Scheduler::addNewProcess(Process* newProcess)
{
	newProcess->setState(NEW);
	newList.push(newProcess);
}

void Scheduler::addProcessor(Processor* Processor)
{
	processorList.push(Processor);
}


void Scheduler::addKillSignal(KillSignal signal)
{
	killList.push(signal);
}

void Scheduler::terminateProcess(Process* finishedProcess)
{
	finishedProcess->setState(TRM);
	totalTurnaroundTime += finishedProcess->getTurnaroundTime();
	trmList.push(finishedProcess);
}

void Scheduler::scheduleProcess(Process* process)
{
	process->setState(RDY);
	//add to the ready queue of the processor
}

void Scheduler::killProcess(KillSignal signal)
{

}


void Scheduler::testRun()
{
	clk->incrementTime();
}

void Scheduler::run()
{
	clk->incrementTime();
}




