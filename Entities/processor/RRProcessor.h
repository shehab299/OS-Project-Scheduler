#pragma once

#include "../../Control/Scheduler.h"
#include"../../Utils/DS/CircularQueue.h"
#include "Processor.h"


class RRProcessor : public Processor
{
private:
	int timeSlice;
	int remainingTime;
	CircularQueue<Process*> readyQueue;
public:
	RRProcessor(int id, int timeSlice);
	virtual void addProcess(Process* process);
	virtual void getNextProcess();
	virtual void run();
	virtual void killProcess(KillSignal sig);
	virtual int getProcessorType();
	virtual std::string toString();
	virtual int getProcessorLoad();
	virtual bool isReadyEmpty();
	virtual Process* stolenItem();
	virtual void removeFromReady(int id);
};
