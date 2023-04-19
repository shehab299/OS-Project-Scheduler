#pragma once

#include "../../Control/Scheduler.h"
#include "Processor.h"
#include "../../Utils/DS/PriorityQueue.h"

class SJFProcessor : public Processor
{
private:
	PriorityQueue<Process*> readyQueue; //To be edited: it has to be Priority Queue
public:
	SJFProcessor(int id);
	virtual void addProcess(Process* process);
	virtual void getNextProcess();
	void killProcess(KillSignal signal);
	virtual void run();
	virtual int getProcessorType();
	virtual bool isProcessIn(int id);
	virtual std::string toString();
};
