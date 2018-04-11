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

            

        }
    }      
}

// Job Scheduler::createJob(string line){



// }

