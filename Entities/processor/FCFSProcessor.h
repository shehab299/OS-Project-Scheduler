#pragma once

#include "Processor.h"
#include "../../Control/Scheduler.h"
#include"../../Utils/DS/LinkedList.h"
#include"../../Utils/Defs.h"

class FCFSProcessor : public Processor
{
private:
	LinkedList<Process*> readyQueue;
public:
	FCFSProcessor();
	virtual void addProcess(Process* process);
	virtual void getNextProcess();
	virtual void run();
	void killProcess(KillSignal sigkill);
};



