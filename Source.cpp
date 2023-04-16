#include <iostream>
#include "Control/Simulator.h"

#include "Utils/DS/PriorityQueue.h"
#include "Utils/DS/MinHeap.h"

using std::cin;
using std::string;

int main()
{

	PiorityQueue<int> pq;
	pq.enqueue(1);
	pq.enqueue(-1);
	pq.enqueue(100);
	pq.enqueue(50);

	while (!pq.isEmpty())
	{
		cout << pq.peek() << " ";
		pq.dequeue();
	}


/*
	Simulator newSimulator;

	string fileName;
	cin >> fileName;

	newSimulator.readInitFile(fileName);
	newSimulator.runSimulation();
*/
}
