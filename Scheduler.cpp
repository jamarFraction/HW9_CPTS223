#include "Scheduler.h"

Scheduler::Scheduler(int numberOfProcessors){

    this->freeProcessors = numberOfProcessors;
}

Scheduler::~Scheduler(){}


void Scheduler::RunScheduler(ifstream &inputFile){

    
    while(!inputFile.eof()){

        //read a line from the file
        string line = "";

        getline(inputFile, line);

        //verify that this line is not a NULL job
        if(line.substr(0, line.find(" ")) != "NULL"){

            Job newJob = createJob(line);

        }
    }      
}

Job Scheduler::createJob(string line){

    //Line processing done by breaking the line up into chunks

    //increment the jobs created count, assign it
    this->createdJobsCount += 1;

    int jobID = createdJobsCount;

    //pos variable used to keep track of the spaces in the line
    //find the first space
    int pos = line.find(" ");

    //grab the job description
    string jobDescription = line.substr(0, pos);

    //update the line to start from the instance of the first space
    line = line.substr(pos + 1);

    //grab the number of processors
    int n_procs = stoi(line.substr(0, line.find(" ")));

    //update the pos to the location of the second space
    pos = line.find(" ");

    //line reflects data following the second space of the OG line
    line = line.substr(pos + 1);

    //grab the number of ticks
    int n_ticks = stoi(line.substr(0, line.find(" ")));

    //create a new job with the required arguments
    return Job(jobID, jobDescription, n_procs, n_ticks);
}

