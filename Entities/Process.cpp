#include "Process.h"
#include <random>
#include <time.h>

Process::Process(int id, int AT, int cpuT , bool isChild) :
	processId(id), arrivalTime(AT), cpuTime(cpuT),
	responseTime(0), waitingTime(-1), terminationTime(-1)
	, turnAroundTime(-1), finishedTime(0), currentIoTime(0), state(NEW), leftChild(nullptr),
	gotToCpuFlag(false) , processorId(-1) , childFlag(isChild) , rightChild(nullptr) , totalIoTime(0)
{

}

int Process::getIoTime() const
{
	return currentIoTime;
}


int Process::getWaitingTime() const
{
	return waitingTime;
}


int Process::getRemainingTime() const
{
	return cpuTime - finishedTime;
}

int Process::getArrivalTime() const
{
	return arrivalTime;
}

int Process::getId() const
{
	return processId;
}

int Process::getTurnaroundTime() const
{
	return turnAroundTime;
}

ProcessState Process::getState() const
{
	return state;
}

void Process::setState(ProcessState newState)
{
	state = newState;
}




int Process::getTerminationTime() const
{
	return terminationTime;
}

void Process::setResponseTime(int time)
{
	responseTime = time;
}

void Process::setProcessorId(int id)
{
	processorId = id;
}

int Process::getTotalIoTime() const
{
	return totalIoTime;
}

void Process::setTerminationTime(int time)
{
	terminationTime = time + 1;
	turnAroundTime = terminationTime - arrivalTime ; 
	waitingTime = turnAroundTime - finishedTime;
}

void Process::setWaitingTimeSoFar(int time)
{
	waitingTime = (time - arrivalTime) - (finishedTime);
}



void Process::setIoTime(int time)
{
	if (time > 0) {
		currentIoTime = time;
		totalIoTime += time;
	}
}


// add a request to the list of io requests of the process
void Process::setIoRequest(IoRequest newR)
{
	ioRequests.push(newR);
}

bool Process::isFinished() const
{
	return (cpuTime <= finishedTime);
}

int Process::getProcessorLocation() const
{
	return processorId - 1;
}

// checks if the process is asking for an io request 
// you handle the request if it is asking
bool Process::needsIO()
{
	if (!ioRequests.empty())
	{
		IoRequest currentIo = ioRequests.front();
		if (currentIo.ioTime == finishedTime)
		{
			setIoTime(currentIo.ioDuration);
			ioRequests.pop();
			return true;
		}
	}
	return false;
}

bool Process::gotToCpu()
{
	return gotToCpuFlag;
}

bool Process::requestFork()
{
	// if it already have a child
	if (leftChild && rightChild)
		return false;

	//generate random number
	unsigned int seed = int(time(0));
	srand(seed);
	int randNum = rand() % 100;

	if (randNum <= forkProp)
		return true;
	
	return false;
}



int Process::getResponseTime() const
{
	return responseTime;
}

bool Process::shouldMigrateToSFJ()
{
	if (getRemainingTime() < RTF && !childFlag)
		return true;
	else
		return false;
}

bool Process::shouldMigrateToRR()
{
	if (waitingTime > maxWait && !childFlag)
		return true;
	else
		return false;
}

Process* Process::getLeftChild() const
{
	return leftChild;
}

Process* Process::getRightChild() const
{
	return rightChild;
}


int Process::getcpu() const
{
	return cpuTime;
}

bool Process::isChild() const
{
	return childFlag;
}

void Process::setFlag()
{
	gotToCpuFlag = true;
}

void Process::setLeftChild(Process* process)
{
	if(process)
		leftChild = process;
}

void Process::setRightChild(Process* process)
{
	if (process)
		rightChild = process;
}


// simulate executing Io operations
void Process::runIO()
{
	if(currentIoTime)
		currentIoTime--;
}

// simulate executing the process
void Process::run()
{
	finishedTime++;
}


Process::~Process()
{

}

bool Process::operator<(const Process& other)
{
	return (getRemainingTime() < other.getRemainingTime());
}

bool Process::operator>(const Process& other)
{
	return (getRemainingTime() > other.getRemainingTime());
}

std::string to_string(Process* processPtr)
{
	return std::to_string(processPtr->getId());
}
