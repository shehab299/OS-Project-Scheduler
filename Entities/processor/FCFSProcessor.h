#pragma once

#include "Processor.h"

#include "../../Control/Scheduler.h"
#include"../../Utils/Defs.h"
#include "../../Utils/processList.h"

class FCFSProcessor : public Processor
{
private:
	ProcessList readyQueue;
public:
	FCFSProcessor(int id);
	virtual void addProcess(Process* process);
	virtual void getNextProcess();
	virtual void run();
	virtual bool killProcess(KillSignal sigkill);
	virtual void removeFromReady(int id);
	virtual int getProcessorType();
	virtual double getProcessorLoad();
	virtual std::string toString();
	virtual bool isReadyEmpty();
	virtual Process* getStolenItem();
	virtual int getFinishTime();
};



