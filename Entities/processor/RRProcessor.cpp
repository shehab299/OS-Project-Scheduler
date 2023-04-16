#include "RRProcessor.h"

RRProcessor::RRProcessor(int timeSlice) :timeSlice(timeSlice)
{
}

void RRProcessor::addProcess(Process* process)
{
    process->setResponseTime(clk->getTime() - process->getArrivalTime());
    readyQueue.enqueue(process);
}

void RRProcessor::getNextProcess()
{
    if (!readyQueue.isEmpty())
    {
        currentProcess = readyQueue.peek();
        readyQueue.dequeue();
        busy = true;
    }
    else
    {
        currentProcess = nullptr;
        busy = false;
    }
}

void RRProcessor::run()
{
    getNextProcess();
    while (currentProcess)
    {
        // Check if the current process needs I/O before running it
        if (currentProcess->needsIO())
        {
            currentProcess->setState(BLK);
            //-->move to BLK List
            busy = false;
            getNextProcess();
            continue;
        }

        // Run the current process until the end of the time slice or until it finishes
        currentProcess->setState(RUN);
        int remainingTime = timeSlice;
        while (remainingTime > 0 && !currentProcess->isFinished())
        {
            currentProcess->run();
            busyTime++;
            remainingTime--;

            // Check if the process needs I/O during execution
            if (currentProcess->needsIO())
            {
                currentProcess->setState(BLK);
                //ioQueue.push(currentProcess);
                busy = false;
                continue;
            }
        }

        // Check if the process has finished or reached the end of the time slice
        if (currentProcess->isFinished())
        {
            currentProcess->setTerminationTime(clk->getTime());
            schedulerPtr->terminateProcess(currentProcess);
            finishTime = clk->getTime();
            currentProcess = nullptr;
            busy = false;
            getNextProcess();
        }
        else
        {
            currentProcess->setState(RDY);
            readyQueue.enqueue(currentProcess);
        }
        currentProcess = nullptr;
        busy = false;
    }
}
