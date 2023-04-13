#pragma once

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

	IoRequest(int io_t, int io_d) : ioTime(io_t), ioDuration(io_d)
	{}
};
