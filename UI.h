#pragma once
#include"../Control/Scheduler.h"
#include "../Entities/processor/FCFSProcessor.h"
#include "../Entities/processor/RRProcessor.h"
#include "../Entities/processor/SJFProcessor.h"
#include "../Entities/IO.h"
#include "../Entities/Clock.h"
class UI
{
private:
	Scheduler * schedulerPtr;
	Clock* clkPtr;
	FCFSProcessor * fcfsPtr;
	RRProcessor * rrPtr;
	SJFProcessor * sjfPtr;
	IO* ioPtr;
public:
	void finalUI();



};

