#pragma once

#include "Process.h"

#include <queue>

class IO
{
private:
	std::queue <Process*> blkList;
	Process* allocated;
public:
	IO();
	void addToBlk(Process* blockedProcess);
	void allocateIO();
	void runIo();
	bool isBusy();
};

