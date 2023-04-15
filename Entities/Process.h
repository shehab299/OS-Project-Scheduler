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
	int currentIoTime;
	ProcessState state;
	std::queue <IoRequest> ioRequests;
	Process* child;
public:
	Process(int id, int AT, int cpuT);
	int getIoTime() const;
	int getWaitingTime() const;
	int getRemainingTime() const;
	int getProcessId() const;
	int getTurnaroundTime() const;
	ProcessState getState() const;
	void setState(ProcessState newState);
	void setResponseTime(int time);
	void setTerminationTime(int time);
	void setIoTime(int time);
	void setIoRequest(IoRequest newR);
	bool isFinished() const;
	bool needsIO();
	void run();
	void runIO();
	~Process();
};

