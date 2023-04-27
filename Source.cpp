#include <iostream>
#include "Control/Simulator.h"

#include "Entities/processor/FCFSProcessor.h"
#include "Entities/processor/SJFProcessor.h"
#include "Entities/processor/RRProcessor.h"

#include "Utils/DS/PriorityQueue.h"
#include "Utils/DS/MinHeap.h"


using std::cin;
using std::string;

int main()
{
	Simulator newSimulator;
	string fileName;

	cout << "Please Input The File Name To Instantiate Simulation" << endl << "> ";
	cin >> fileName;

	newSimulator.readInitFile(fileName);
	newSimulator.runSimulation();
}
