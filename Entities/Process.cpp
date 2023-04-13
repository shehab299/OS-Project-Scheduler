#include "Process.h"

Process::Process(int id, int AT, int cpuT) :
	processId(id), arrivalTime(AT), cpuTime(cpuT),
	responseTime(-1), waitingTime(-1), terminationTime(-1)
	, turnAroundTime(-1), finishedTime(0), ioTime(0), state(NEW)
{}

int Process::getIoTime() const
{
	return ioTime;
}

int Process::getWaitingTime() const
{
	return waitingTime;
}

int Process::getRemainingTime() const
{
	return cpuTime - finishedTime;
}

int Process::getProcessId() const
{
	return processId
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
		ioTime = time;
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

// simulate executing Io operations
void Process::runIO()
{
	if(state == BLK)
		ioTime--;
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


