#pragma once
#include"../../Utils/DS/CircularQueue.h"
#include "Processor.h"
class RRProcessor : public Processor
{
private:
		int timeSlice;
		CircularQueue<Process*> readyQueue;
public:
	RRProcessor(int timeSlice);
	virtual void addProcess(Process* process);
	virtual void getNextProcess();
	virtual void run();
};
