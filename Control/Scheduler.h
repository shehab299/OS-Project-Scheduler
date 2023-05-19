#pragma once

#include <sstream>

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

	int STL; // Time for Stealing
	
	int nBusyProcessors;
	int nProcesses;

	int numberFcfs;
	int numberRR;
	int numberSJF;

	//Statistics
    int totalWaitTime;
	int totalResponseTime;
	int totalTurnaroundTime;

	int migrationRTFcnt;
	int migrationMAXWcnt;
	int stealCnt;
	int forkCnt;
	int KillCnt;



	Queue<Process*> newList;
	Queue<Process*> trmList;
	Queue<KillSignal> killList;

	double getStealProb();
	double getMigrationtoRRProb();
	double getMigrationtoSJFProb();
	double getForkProb();
	double getKillProb();
	
	int getMinProcessorIndex();
	int getMinFCFSProcessorIndex();	
	int getMinRRProcessorIndex();
	int getMinSJFProcessorIndex();
	
	void updateStatistics(Process* processPtr);

	std::string getProcessSummary(Process* processPtr);

public:
	
	Scheduler(int nFcfs, int nRR, int nSJF, int stl);

	int getTotalTurnTime() const;
	int getNTerminated();
	double calculateStealPercent(Processor* shorteset, Processor* longest);
	void setClock(Clock* clkPtr);
	void setNProcesses(int nProcesses);

	int getNumberSJF() const;
	int getNumberRR() const;

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

	void migrateToRR(Process* process);
	void migrateToSJF(Process* process);

	std::string getIoInfo();
	std::string getRunningInfo();
	std::string getTerminatedInfo();
	std::string getProcessorsInfo();
	std::string getStatistics();

	bool isFinished();

	void workStealing();
	void run();

};

