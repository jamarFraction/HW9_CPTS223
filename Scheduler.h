#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <fstream>
#include <iostream>
#include "Job.h"
#include "BinaryHeap.h"
#include "JobQueue.h"

using std::istream;
using namespace std;

class Scheduler
{

    // Scheduler class
    //
    // CONSTRUCTION: with an optional number of processors (that defaults to 1)
    //
    // ******************PUBLIC OPERATIONS*********************
    // void RunScheduler(ifstream &inputFile)  --> Run the scheduler with the passed input job list
    // void RunScheduler()                     --> Run the scheduler for manual entry

  public:
    Scheduler(int numberOfProcessors = 1);

    ~Scheduler();

    //Scheduler driver for testing
    void RunScheduler(istream &inputFile);

    //Scheduler driver for user input
    void RunScheduler();

  private:
    //wait queue for holding jobs
    BinaryHeap waitQueue;

    //Running job queue
    JobQueue runningJobQueue;

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

    //Private Class Functions
    //*******************************************************************************
    //*******************************************************************************
    //*******************************************************************************

    //Controls a tick process in its entirety, returns true if user enters "exit" in job prompt
    bool Tick(istream &inputFile = std::cin);

    //function that given the string representation of a job will return a Job object
    //format "description n_procs n_ticks"
    Job CreateJob(string line);

    //Job insertion function
    void InsertJob(Job &newJob);

    //Displays the log containing the tick log
    void DisplayTickLog();

    //Creates a job or not --- inserts into the waiting queue based on file input
    void AutoLine_JobCreate(istream &inputFile);

    //Creates a job or not --- inserts into the waiting queue based on user input
    //root determinant of termination of Scheduler
    bool ManualLine_JobCreate();

    //returns the job in the wait queue requiring the least amount of processors
    Job FindShortest();

    //returns true if there are sufficient processors availble to initiate the
    //passed job during the current tick
    bool CheckAvailability(Job &minJob) const;

    //Removes the shortest n_procs Job from the wait queue
    void DeleteShortest();

    //Insert the job into the running pool
    void RunJob(Job &newJob);

    //Process the wait queue by inserting shortest length jobs into running queue
    void ProcessWaitQueue();

    //Decrements the number of remaining ticks for each job in the running queue
    void DecrementTimer();

    //Releases processors to free pool as jobs complete
    void ReleaseProcs();
};
#endif