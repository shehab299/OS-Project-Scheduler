#pragma once

#include "../Process.h"
#include "../Clock.h"

class Scheduler;


class Processor
{
protected:
	bool busy;
	int busyTime;
	int expectedFinishTime;
	int freeTime;
	Process* currentProcess;
	Clock* clk;
	Scheduler* schedulerPtr;
public:
	Processor();
	void setSchedulerPtr(Scheduler* scheduler);
	int getFinishTime();
	virtual void killProcess(KillSignal signal) = 0;
	virtual int getProcessorType() = 0;
	virtual void getNextProcess() = 0;
	virtual Process* getRunningProcess();
	virtual void addProcess(Process* process) = 0;
	virtual void run() = 0;
	virtual void testRun();
	virtual void DisplayReady()=0;
	virtual bool isProcessIn(int id) = 0;
	bool isBusy();
	int getUtilization();
};

