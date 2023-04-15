#pragma once
#include <fstream>


using std::ifstream;



enum ProcessState
{
	NEW = 0,
	RDY,
	RUN,
	BLK,
	TRM,
	ORPH
};


struct IoRequest
{
	int ioTime;
	int ioDuration;

	IoRequest() : ioTime(0) , ioDuration(0)
	{}

	IoRequest(int io_t, int io_d) : ioTime(io_t), ioDuration(io_d)
	{}

	friend ifstream& operator>>(ifstream& is, IoRequest& req);

};

ifstream& operator>>(ifstream& is, IoRequest& req) 
{
	char leftP, comma, rightP;

	is >> leftP;
	is >> req.ioTime >> comma >>  req.ioDuration;
	is >> rightP;

	return is;
}


struct KillSignal
{
	int processId;
	int timeToKill;

	KillSignal() : processId(0) , timeToKill(0)
	{}

	KillSignal(int pid, int time) : processId(pid), timeToKill(time)
	{}

	friend ifstream& operator>>(ifstream& is, KillSignal& sianal);
};

ifstream& operator>>(ifstream& is, KillSignal& signal)
{
	is >> signal.timeToKill >> signal.processId;
	return is;
}