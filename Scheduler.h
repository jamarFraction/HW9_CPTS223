#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <fstream>
#include <iostream>
#include "Job.h"
#include "BinaryHeap.h"

using std::ifstream;
using namespace std;

class Scheduler{

    // Scheduler class
    //
    // CONSTRUCTION: with an optional number of processors (that defaults to 1)
    //
    // ******************PUBLIC OPERATIONS*********************
    // void RunScheduler(ifstream &inputFile)  --> Run the scheduler with the passed input job list
    

    public: 
    Scheduler(int numberOfProcessors = 1);

    ~Scheduler();

    //Scheduler driver for testing
    void RunScheduler(ifstream &inputFile);

    //Scheduler driver for user input
    void RunScheduler();


    private:

    //wait queue for holding jobs
    BinaryHeap waitQueue;

    //Max number of processors capable of running in this cluster
    int processorCount;

    //free processor count
    int freeProcessors;

    //Keeps track of the number of jobs created, also used to asign jobID's
    int createdJobsCount;

    //Keps track of the number of ticks since start
    int numberOfTicks;

    //String representation of the sequence of events/errors for the current tick
    string currentTickLog;

    //function that given the string representation of a job will return a Job object
    Job CreateJob(string line);

    //Job insertion function
    void InsertJob(Job &newJob);

    //User ticks
    bool Tick();

    //Ticks using input file (for test)
    void Tick(ifstream &inputFile);

    //Displays the log containing the tick log
    void DisplayTickLog();
};


#endif