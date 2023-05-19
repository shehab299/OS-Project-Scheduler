#include "Clock.h"

Clock::Clock() : currenTime(1)
{}

void Clock::incrementTime()
{
	currenTime++;
}

int Clock::getTime()
{
	return currenTime;
}



