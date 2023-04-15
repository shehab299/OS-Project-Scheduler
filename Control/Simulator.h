#pragma once

#include "Scheduler.h"
#include "../Entities/Clock.h"
#include <string>

using std::string;

class Simulator
{
private:
	Scheduler* schedulerPtr;
	Clock* clk;
	bool initialized;
public:
	Simulator();
	bool readInitFile(string fileName);
	bool runSimulation();
};
