#pragma once
#include "../Utils/Defs.h"
#include <queue>

class Process
{
private:
	const int processId;
	const int arrivalTime;
	const int cpuTime;
	int responseTime;
	int terminationTime;
	int turnAroundTime;
	int waitingTime;
	int finishedTime;
	int ioTime;
	ProcessState state;
	std::queue <IoRequest> ioRequests;

public:
	Process(int id, int AT, int cpuT);
	int getIoTime() const;
	int getWaitingTime() const;
	int getRemainingTime() const;
	void setState(ProcessState newState);
	void setResponseTime(int time);
	void setTerminationTime(int time);
	void setIoTime(int time);
	bool isFinished() const;
	bool needsIO();
	void run();
	void runIO();

};

