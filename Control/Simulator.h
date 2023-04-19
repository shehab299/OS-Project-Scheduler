#pragma once

#include "Scheduler.h"
#include "../Entities/Clock.h"
#include "../User/UI.h"
#include <string>

using std::string;

class Simulator
{
private:
	Scheduler* schedulerPtr;
	UI* userInterface;
	Clock* clk;
	int nProcesses;
	bool initialized;
public:
	Simulator();
	bool readInitFile(string fileName);
	bool runSimulation();
};
