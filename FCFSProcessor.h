#pragma once

#include "Processor.h"

#include "../../Control/Scheduler.h"
#include"../../Utils/Defs.h"
#include "../../Utils/DS/LinkedLish.h"


class FCFSProcessor : public Processor
{
private:
	List<Process*> readyQueue;
public:
	FCFSProcessor();
	virtual void addProcess(Process* process);
	virtual void getNextProcess();
	virtual void run();
	virtual void DisplayReady();
	virtual void killProcess(KillSignal sigkill);
	bool isProcessIn(int id);
	virtual int getProcessorType();
};



