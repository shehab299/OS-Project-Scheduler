#include "Clock.h"

Clock::Clock() : currenTime(0)
{}

void Clock::incrementTime()
{
	currenTime++;
}

int Clock::getTime()
{
	return currenTime;
}



