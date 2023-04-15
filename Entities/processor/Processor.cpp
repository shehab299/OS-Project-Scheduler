#include "Processor.h"

Processor::Processor():busy(false),busyTime(0),freeTime(0),currentProcess(nullptr)
{
  
}

bool Processor::isBusy()
{
    return busy;
}

int Processor::getUtilization()
{
    return (busyTime / (busyTime + freeTime));
}
