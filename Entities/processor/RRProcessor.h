#pragma once

#include "../../Control/Scheduler.h"
#include"../../Utils/DS/Queue.h"
#include "Processor.h"


class RRProcessor : public Processor
{
private:
	int timeSlice;
	int remainingTime;
	Queue<Process*> readyQueue;
public:
	RRProcessor(int id, int timeSlice);
	virtual void addProcess(Process* process);
	virtual void getNextProcess();
	virtual void run();
	virtual bool killProcess(KillSignal sig);
	virtual int getProcessorType();
	virtual std::string toString();
	virtual double getProcessorLoad();
	virtual bool isReadyEmpty();
	virtual Process* getStolenItem();
	virtual void removeFromReady(int id);
	virtual int getFinishTime();
};
