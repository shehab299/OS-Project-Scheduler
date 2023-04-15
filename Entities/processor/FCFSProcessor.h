#pragma once

#include "Processor.h"
#include"../../Utils/DataStructure/LinkedList.h"

class FCFSProcessor : public Processor
{
private:
	LinkedList<Process*> readyQueue;
public:
	FCFSProcessor();
	virtual int getFinishTime();
	virtual void addProcess(Process* process);
	virtual void run(int clock);
	void killProcess(int processId, int sigKill);
	virtual void getNextProcess(int clock);
	
};

