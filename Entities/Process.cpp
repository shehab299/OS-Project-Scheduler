#include "Process.h"

Process::Process(int id, int AT, int cpuT) :
	processId(id), arrivalTime(AT), cpuTime(cpuT),
	responseTime(-1), waitingTime(-1), terminationTime(-1)
	, turnAroundTime(-1), finishedTime(0), IO_time(0), state(NEW)
{}

int Process::getIoTime() const
{
	return IO_time;
}

int Process::getWaitingTime() const
{
	return waitingTime;
}

int Process::getRemainingTime() const
{
	return cpuTime - finishedTime;
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

bool Process::isFinished() const
{
	return (cpuTime == finishedTime);
}

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

void Process::runIO()
{
	ioTime--;
}

void Process::run()
{
	finishedTime++;
}

