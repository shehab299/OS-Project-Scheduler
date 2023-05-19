#pragma once

#include "../../Control/Scheduler.h"
#include "Processor.h"
#include "../../Utils/DS/PriorityQueue.h"


class SJFProcessor : public Processor
{
private:
	PriorityQueue<Process*,1> readyQueue; 
public:
	SJFProcessor(int id);
	virtual void addProcess(Process* process);
	virtual void getNextProcess();
	bool killProcess(KillSignal signal);
	virtual void run();
	virtual int getProcessorType();
	virtual bool isProcessIn(int id);
	virtual std::string toString();
	virtual double getProcessorLoad();
	virtual bool isReadyEmpty();
	virtual Process* getStolenItem();
	virtual void removeFromReady(int id);
	int getFinishTime();
};
