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
	newList.enqueue(newProcess);
}

void Scheduler::addProcessor(Processor* Processor)
{
	processorList.enqueue(Processor);
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
	process->setState(RDY);
	//add to the ready queue of the processor
}

void Scheduler::killProcess(KillSignal signal)
{

}


void Scheduler::testRun()
{
	while (!newList.isEmpty() && newList.peek()->getArrivalTime() == clk->getTime()) {
		scheduleProcess(newList.peek());
		newList.dequeue();
	}

	//begin
	// call the run function for all processess
	// for each processor in processor list
	// processor -> run()
	// end

	clk->incrementTime();
}

void Scheduler::run()
{
	clk->incrementTime();
}




