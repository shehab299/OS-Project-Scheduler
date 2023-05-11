#include "Process.h"
#include <random>
#include <time.h>

Process::Process(int id, int AT, int cpuT , bool isChild) :
	processId(id), arrivalTime(AT), cpuTime(cpuT),
	responseTime(-1), waitingTime(-1), terminationTime(-1)
	, turnAroundTime(-1), finishedTime(0), currentIoTime(0), state(NEW), child(nullptr),
	gotToCpuFlag(false) , processorId(-1) , childFlag(isChild)
{}

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

void Process::setChild(Process* process)
{
	if(!child)
		child = process;
}

void Process::setResponseTime(int time)
{
	responseTime = (time > 0) ? time : responseTime;
}

void Process::setProcessorId(int id)
{
	processorId = id;
}

void Process::setTerminationTime(int time)
{
	terminationTime = (time > 0) ? time : terminationTime;
	turnAroundTime = terminationTime - arrivalTime;
}

void Process::setIoTime(int time)
{
	if (time > 0)
		currentIoTime = time;
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
	return processorId;
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
	if (child)
		return false;

	//generate random number
	srand(time(0));
	int randNum = rand() % 100;

	if (randNum <= forkProp)
		return true;
	
	return false;
}

bool Process::isChild() const
{
	return childFlag;
}

void Process::setFlag()
{
	gotToCpuFlag = true;
}

// simulate executing Io operations
void Process::runIO()
{
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
	return cpuTime < other.cpuTime;
}

bool Process::operator>(const Process& other)
{
	return cpuTime > other.cpuTime;
}

std::string to_string(Process* processPtr)
{
	return std::to_string(processPtr->getId());
}
