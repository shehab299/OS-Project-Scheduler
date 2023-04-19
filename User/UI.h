#pragma once

#include <conio.h>
#include "../Control/Scheduler.h"


class UI
{
private:
	Scheduler* schedulerPtr;
	Clock* clk;
public:
	UI(Scheduler* Sptr , Clock* clk);

	void waitForUserPress();
	UI_Mode getWorkingMode();
	void printInfo();
};

