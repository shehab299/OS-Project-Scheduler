#include "Simulator.h"

#include "Scheduler.h"
#include "../Entities/Process.h"
#include "../Entities/processor/Processor.h"
#include "../Entities/processor/FCFSProcessor.h"
#include "../Entities/processor/RRProcessor.h"
#include "../Entities/processor/SJFProcessor.h"
#include "../User/UI.h"
#include "../Entities/Process.h"
#include "Windows.h"

int Process::forkProp = 0;


#include <fstream>
using std::ifstream;


Simulator::Simulator() : schedulerPtr(nullptr), initialized(false), clk(new Clock())
, nProcesses(0), userInterface(nullptr)
{
}

bool Simulator::readInitFile(string fileName)
{
	ifstream initFile;
	initFile.open(fileName);

    if (!initFile.is_open()) // If file is not open, return false.
        return false;

    if (!initFile.good()) // If file is not good, return false.
        return false;

    // Read in the number of processors of each type.
    int numberFcfs, numberRR, numberSJF;
    initFile >> numberFcfs >> numberSJF >> numberRR;

    // Read in the time slice for the round robin processors.
    int timeSlice;
    initFile >> timeSlice;

    // Read in the parameters for the scheduler.
    int RTF, MaxW, STL, forkProp;
    initFile >> RTF >> MaxW >> STL >> forkProp;

    Process::setForkProbality(forkProp);

    // Create a new scheduler with the specified parameters.
    schedulerPtr = new Scheduler(RTF, MaxW, STL, forkProp);
    schedulerPtr->setClock(clk);
    
    int id = 0;
    // Add the specified number of FCFS processors to the scheduler.
    for (int i = 0; i < numberFcfs; i++)
    {
        Processor* newProcessor = new FCFSProcessor(++id);
        newProcessor->setSchedulerPtr(schedulerPtr);
        newProcessor->setClk(clk);
        schedulerPtr->addProcessor(newProcessor);
    }

    // Add the specified number of round robin processors to the scheduler.
    for (int i = 0; i < numberRR; i++)
    {
        Processor* newProcessor = new RRProcessor(++id ,timeSlice);
        newProcessor->setSchedulerPtr(schedulerPtr);
        newProcessor->setClk(clk);
        schedulerPtr->addProcessor(newProcessor);

    }

    // Add the specified number of SJF processors to the scheduler.
    for (int i = 0; i < numberSJF; i++)
    {
        Processor* newProcessor = new SJFProcessor(++id);
        newProcessor->setSchedulerPtr(schedulerPtr);
        newProcessor->setClk(clk);
        schedulerPtr->addProcessor(newProcessor);
    }

    // Read in the number of processes to create.
   
    initFile >> nProcesses;
    schedulerPtr->setNProcesses(nProcesses);
  
    // Create each process and add it to the scheduler.
    for (int i = 0; i < nProcesses; i++)
    {
        int AT, pId, cpuT, nRequests;

        // Read in the arrival time, process ID, CPU time, and number of I/O requests.
        initFile >> AT >> pId >> cpuT >> nRequests;

        // Create a new process with the specified parameters.
        Process* newProcess = new Process(pId, AT, cpuT);

        // Add each I/O request to the process.
        for (int i = 0; i < nRequests; i++)
        {
            char comma;
            IoRequest req;

            req >> initFile;

            // If this is not the last I/O request, read in the comma as well.
            if (i != nRequests - 1)
                initFile >> comma;

            newProcess->setIoRequest(req);
        }

        // Add the process to the scheduler.
        schedulerPtr->addNewProcess(newProcess);
    }

    // Read in any kill signals and add them to the scheduler.
    string line;
    getline(initFile, line);

    while (!initFile.eof())
    {
        KillSignal sig;

        sig >> initFile;

        schedulerPtr->addKillSignal(sig);
    }

    initFile.close(); // Close the initialization file.

    userInterface = new UI(schedulerPtr, clk);
    initialized = true;
    return true;
}

bool Simulator::runSimulation()
{ 
    if (!initialized)
        return false;

    UI_Mode mode = userInterface->getWorkingMode();
    
    while (nProcesses != schedulerPtr->getNTerminated()) 
    {
        schedulerPtr->run();

        switch (mode)
        {
        case Interactive:
            userInterface->printInfo();
            userInterface->waitForUserPress();
            break;
        case StepByStep:
            userInterface->printInfo();
            Sleep(1000);
        case Silent:
            break;
        default:
            break;
        }

        clk->incrementTime();
    }

    return true;
}
