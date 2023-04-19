#include "UI.h"
#include <cstdio>


UI::UI(Scheduler* Sptr, Clock* clk) : schedulerPtr(Sptr) , clk(clk)
{
}



void UI::waitForUserPress()
{
	std::cout << "Press any key to continue...\n";
	getchar();
}

UI_Mode UI::getWorkingMode()
{
	int mode;
	std::cout << "Please choose a mode t:\n";
	std::cout << "1. Interactive Mode\n";
	std::cout << "2. Step By Step Mode\n";
	std::cout << "3. Silent Mode\n";
	std::cout << "> ";
	std::cin >> mode;

	switch (mode)
	{
	case 1: return Interactive;
	case 2: return StepByStep;
	case 3: return Silent;
	default :
		cout << "Please Input Valid Mode Number\n";
		return getWorkingMode();
	}

}

void UI::printInfo()
{
	std::cout << "Current Timestep:" << clk->getTime() << std::endl;
	cout << "-----------------   RDY processes  -------------------" << std::endl;
	cout << schedulerPtr->getProcessorsInfo() << endl;
	cout << "-----------------   BLK processes  -------------------" << std::endl;
	cout << schedulerPtr->getIoInfo() << endl;
	cout << "-----------------   RUN processes  -------------------" << std::endl;
	cout << schedulerPtr->getRunningInfo() << endl;
	cout << "-----------------   TRM processes  -------------------" << std::endl;
	cout << schedulerPtr->getTerminatedInfo() << endl;
	cout << "------------------------------------------------------" << std::endl;
}


