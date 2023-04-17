#include "Process.h"

Process::Process(int id, int AT, int cpuT) :
	processId(id), arrivalTime(AT), cpuTime(cpuT),
	responseTime(-1), waitingTime(-1), terminationTime(-1)
	, turnAroundTime(-1), finishedTime(0), currentIoTime(0), state(NEW), child(nullptr),
	gotToCpuFlag(false)
{}

int Process::getIoTime() const
{
	return currentIoTime;
}

int Process::getId() const
{
	return processId;
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

int Process::getProcessId() const
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

void Process::setResponseTime(int time)
{
	responseTime = (time > 0) ? time : responseTime;
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
	return (cpuTime == finishedTime);
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

void Process::setFlag()
{
	gotToCpuFlag = true;
}

// simulate executing Io operations
void Process::runIO()
{
	if(state == BLK)
		currentIoTime--;
}

// simulate executing the process
void Process::run()
{
	finishedTime++;
}


Process::~Process()
{
	delete child;
}


