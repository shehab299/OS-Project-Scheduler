#pragma once

#include "Process.h"
#include "../Utils/DS/Queue.h"

class my_IO
{
private:
	Queue <Process*> blkList;
	Process* allocated;
public:
	my_IO();
	void addToBlk(Process* blockedProcess);
	void allocateIO();
	void runIo();
	std::string toString();
	Process* getAllocated();
	bool isBusy();
};

