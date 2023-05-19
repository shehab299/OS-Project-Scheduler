#include "UI.h"
#include <cstdio>
#include <Windows.h>

UI::UI(Scheduler* Sptr, Clock* clk) : schedulerPtr(Sptr) , clk(clk)
{
}



void UI::waitForUserPress()
{
	std::cout << "Press any key to continue...\n";
	getchar();
}

void UI::shoWelcomeMessage()
{
	std::cout << "-------------------------------------------------------------------";
	std::cout << endl;
	std::cout << "              Welcome To OS Scheduler Simulator                    ";
	std::cout << endl;
	std::cout << "-------------------------------------------------------------------";

	std::cout << endl;
}

void UI::showStartingMessage()
{
	cout << "Simulation Started.";
	for (int i = 0; i < 5; i++)
	{
		Sleep(500);
		cout << ".";
	}
	cout << endl;
}

void UI::showEndingMessage()
{
	cout << "Simulation Ended Successfully" << endl;
	cout << "Statistics Files has been created in Results Folder" << endl;
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


