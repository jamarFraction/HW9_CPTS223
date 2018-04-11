#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <fstream>
#include "Job.h"
#include "BinaryHeap.h"

using std::ifstream;

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

    void RunScheduler(ifstream &inputFile);


    private:

    //free processor count
    int freeProcessors;

    //Keeps track of the number of jobs created, also used to asign jobID's
    int createdJobsCount;

    //function that given the string representation of a job will return a Job object
    Job createJob(string line);
};


#endif