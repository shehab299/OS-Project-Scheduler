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
	const int processorId;
	Process* currentProcess;
	Clock* clk;
	Scheduler* schedulerPtr;
public:
	Processor(int id);
	void setSchedulerPtr(Scheduler* scheduler);
	virtual int getFinishTime() = 0;
	int getId();
	virtual bool killProcess(KillSignal signal) = 0;
	virtual int getProcessorType() = 0;
	virtual void getNextProcess() = 0;
	virtual int getRunningId();
	virtual void addProcess(Process* process) = 0;
	virtual void run() = 0;
	bool isBusy();
	double getUtilization();
	virtual double getProcessorLoad() = 0;
	void setClk(Clock* clkptr);
	virtual std::string toString() = 0;
	virtual bool isReadyEmpty() = 0;
	virtual Process* getStolenItem() = 0;
	virtual void removeFromReady(int id) = 0;
};




