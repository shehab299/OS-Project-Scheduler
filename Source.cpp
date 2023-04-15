#include <iostream>
#include "Control/Simulator.h"

using std::cin;
using std::string;

int main()
{
	Simulator newSimulator;

	string fileName;
	cin >> fileName;

	newSimulator.readInitFile(fileName);
	newSimulator.runSimulation();

}
