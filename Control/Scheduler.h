#pragma once


#include "../Utils/Defs.h"
#include "../Entities/Process.h"
#include "../Entities/processor/Processor.h"
#include "../Entities/IO.h"
#include "../Entities/Clock.h"

#include "../Utils/DS/Queue.h"

class Scheduler
{
private:
	IO ioHandler;
	Clock* clk;
	Processor** processorList;
	
	int RR_RTF; // Threshold for migration
	int FCFS_MaxWait; // Max Waiting time for fcfs
	int STL; // Time for Stealing
	int forkProp; // forking probability

	Queue<Process*> newList;
	Queue<Process*> trmList;
	Queue<KillSignal> killList;

	int totalTurnaroundTime;
	
public:
	Scheduler(int rtf , int maxW , int stl , int forkProp);

	int getTotalTurnTime() const;
	void setClock(Clock* clkPtr);

	void addNewProcess(Process* newProcess);
	void addProcessor(Processor* Processor);
	void addKillSignal(KillSignal signal);
	void scheduleProcess(Process* process);

	void blockProcess(Process* blockedProcess);
	void terminateProcess(Process* finishedProcess);
	void killProcess(KillSignal signal);

	void testRun();
	void run();


};

