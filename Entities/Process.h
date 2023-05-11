#pragma once


#include "../Utils/Defs.h"
#include <queue>
#include <iostream>
#include <string>

class Process
{
private:
	static int forkProp;
	const int processId;
	const int arrivalTime;
	const int cpuTime;
	int responseTime;
	int terminationTime;
	int turnAroundTime;
	int waitingTime;
	int finishedTime;
	int currentIoTime;
	int processorId;
	bool gotToCpuFlag;
	bool childFlag;
	ProcessState state;
	std::queue <IoRequest> ioRequests;

	Process* leftChild;
	Process* rightChild;

public:

	Process(int id, int AT, int cpuT , bool isChild = false);
	
	int getId() const;
	int getArrivalTime() const;
	int getWaitingTime() const;
	int getRemainingTime() const;
	int getIoTime() const;
	int getTurnaroundTime() const;
	ProcessState getState() const;
	int getProcessorLocation() const;
	Process* getLeftChild() const;
	Process* getRightChild() const;


	bool isFinished() const;
	bool isChild() const;
	bool needsIO();
	bool gotToCpu();
	bool requestFork();

	void setProcessorId(int id);
	void setLeftChild(Process* process);
	void setRightChild(Process* process);
	void setResponseTime(int time);
	void setTerminationTime(int time);
	void setState(ProcessState newState);
	void setIoTime(int time);
	void setIoRequest(IoRequest newR);
	void setFlag();

	void run();
	void runIO();
	~Process();

	bool operator<(const Process& other);
	bool operator>(const Process& other);

	static void setForkProbality(int prop)
	{
		forkProp = prop;
	}

	static const int getForkProbality()
	{
		return forkProp;
	}

};

std::string to_string(Process* processPtr);
