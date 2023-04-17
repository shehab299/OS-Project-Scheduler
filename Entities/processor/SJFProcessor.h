#pragma once

#include "../../Control/Scheduler.h"
#include "Processor.h"
#include "../../Utils/DS/PriorityQueue.h"

class SJFProcessor : public Processor
{
private:
	PriorityQueue<Process*> readyQueue; //To be edited: it has to be Priority Queue
public:
	virtual void addProcess(Process* process);
	virtual void getNextProcess();
	virtual void run();
};
