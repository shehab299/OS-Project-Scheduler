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

enum ProcessorType
{
	FCFS,
	RR,
	SJF
};


struct IoRequest
{
	int ioTime;
	int ioDuration;

	IoRequest() : ioTime(0) , ioDuration(0)
	{}

	IoRequest(int io_t, int io_d) : ioTime(io_t), ioDuration(io_d)
	{}

	ifstream& operator>>(ifstream& is)
	{
		char leftP, comma, rightP;

		is >> leftP;
		is >> ioTime >> comma >> ioDuration;
		is >> rightP;

		return is;
	}

};




struct KillSignal
{
	int processId;
	int timeToKill;

	KillSignal() : processId(0) , timeToKill(0)
	{}

	KillSignal(int pid, int time) : processId(pid), timeToKill(time)
	{}

	ifstream& operator>>(ifstream& is)
	{
		is >> timeToKill >> processId;
		return is;
	}
};

