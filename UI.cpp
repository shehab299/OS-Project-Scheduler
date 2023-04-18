#include "UI.h"

void UI::finalUI()
{
	cout <<"Current Timestep : " << clkPtr->getTime() << endl;
	cout<<"----------------------  RDY processess  -----------------" << endl;	
	cout << "processor 1  [FCFS]: " << 7 << " RDY: ";
	fcfsPtr->DisplayReady();
	cout << "processor 1  [SJF]: " << 3 << " RDY: ";
	sjfPtr->DisplayReady();
	cout << "processor 1  [RR]: " << 2 << " RDY: ";
	rrPtr->DisplayReady();
	cout << "----------------------  BLK processess  -----------------" << endl;
	cout << 5 << " BLK: ";
	ioPtr->DisplayBlk();
	cout << 3 << " RUN: ";
	schedulerPtr->displayRun();
	cout << 54 << " TRM: ";
	schedulerPtr->displayTerm();
		
}
