#pragma once
#include "../Process.h"
#include"../../Control/Scheduler.h"
class Processor
{
private:
	bool busy;
	Scheduler* schedulerPtr;
protected:
	int busyTime;
	int finishTime;
	int freeTime;
	Process* currentProcess;
public:
	Processor();
	virtual int getFinishTime() = 0; 
	virtual void getNextProcess(int clock) = 0;//get one from the DS
	virtual void run(int clock)=0;
	bool isBusy();
	int getUtilization();
	virtual void addProcess(Process* process) = 0;

};