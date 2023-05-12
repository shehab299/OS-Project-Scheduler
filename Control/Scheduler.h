#pragma once


#include "../Utils/Defs.h"
#include "../Entities/Process.h"
#include "../Entities/processor/Processor.h"
#include "../Entities/IO.h"
#include "../Entities/Clock.h"

#include "../Utils/DS/ArrayList.h"
#include "../Utils/DS/LinkedLish.h"
#include "../Utils/DS/Queue.h"

class Scheduler
{
private:
	IO ioHandler;
	Clock* clk;
	ArrayList<Processor*> processorList;
	
	static const int StealLimit = 40;
	int RR_RTF; // Threshold for migration
	int FCFS_MaxWait; // Max Waiting time for fcfs
	int STL; // Time for Stealing
	int forkProp; // forking probability
	int nBusyProcessors;
	int nProcesses;

	Queue<Process*> newList;
	Queue<Process*> trmList;
	Queue<KillSignal> killList;

	int totalTurnaroundTime;
	
	int getMinProcessorIndex();
	int getMinFCFSProcessorIndex();

public:
	Scheduler(int rtf , int maxW , int stl , int forkProp);

	int getTotalTurnTime() const;
	int getNTerminated();
	double calculateStealPercent(Processor* shorteset, Processor* longest);
	void setClock(Clock* clkPtr);
	void setNProcesses(int nProcesses);

	void addNewProcess(Process* newProcess);
	void addProcessor(Processor* Processor);
	void addKillSignal(KillSignal signal);

	void scheduleProcess(Process* process , bool isForked = false);
	void blockProcess(Process* blockedProcess);
	void terminateProcess(Process* finishedProcess);
	void terminateChildren(Process* process);
	void killProcess(KillSignal signal);
	void forkProcess(Process* process);
	void removeFromReady(Process* process);

	std::string getIoInfo();
	std::string getRunningInfo();
	std::string getTerminatedInfo();
	std::string getProcessorsInfo();

	void workStealing();
	void run();

};

