#include "Scheduler.h"

Scheduler::Scheduler(int numberOfProcessors){

    //Init the cluster processor size and the number of free processors
    this->processorCount = numberOfProcessors;
    this->freeProcessors = numberOfProcessors;
}

Scheduler::~Scheduler(){}


void Scheduler::RunScheduler(ifstream &inputFile){

    system("clear");

    while(!inputFile.eof()){

        this->numberOfTicks += 1;
        cout << "Tick #" << this->numberOfTicks << endl;

        //Perform the tick
        Tick(inputFile);

        //Display the tick log
        DisplayTickLog();
    };

}

void Scheduler::RunScheduler(){

    //controls the continued prompts for more job inserts
    bool terminate = false;

    //clear and ignore what ever may exist in the terminal, will cause issues with input
    system("clear");
    cin.ignore();


    do{

        this->currentTickLog = "";

        //Run the tick function
        terminate = Tick();

        system("clear");

        //Increment the tick and display log info
        this->numberOfTicks += 1;

        cout << "Tick #" << this->numberOfTicks << endl; 

        DisplayTickLog();

    }while(terminate == false);
}

Job Scheduler::CreateJob(string line){

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

void Scheduler::Tick(ifstream &inputFile){

    //read a line from the file
    string line = "";

    getline(inputFile, line);

    //verify that this line is not a NULL job
    if(line.substr(0, line.find(" ")) != "NULL"){

        Job newJob = CreateJob(line);

            //attempt to insert the job into the waiting queue
            InsertJob(newJob);  
        }
    
}

bool Scheduler::Tick(){

    string userInput = "";

    system("clear");
    cout << "Please enter a new job with values separated by spaces (ex. job_description n_procs n_ticks): ";
    //cin.ignore();
    getline(cin, userInput);

    //user wants to create a new job
    if(userInput != "NULL" || userInput != "exit"){

        //create a job with the passed string
        Job newJob = CreateJob(userInput);

        //attempt to insert the job into the waiting queue
        InsertJob(newJob);
    }

    if(userInput == "exit"){

        //return immediately 
        return true;

    }

    //continue with tick process


    
    return false;
}

void Scheduler::InsertJob(Job &newJob){

    //Verify that the cluster has sufficient processors to handle the job
    if(newJob.Get_N_Procs() <= this->processorCount && newJob.Get_N_Ticks() > 0){

        //Cluster has sufficient processors to handle the job, so insert into wait queue
        this->waitQueue.insert(newJob);


    }else{

        //add this error to the tick log
        string error = "Error inserting job: " + to_string(newJob.GetJobID()) + " " + newJob.GetJobDescription() +
        " " + to_string(newJob.Get_N_Procs()) + " " + to_string(newJob.Get_N_Ticks()) + 
        ", required processors larger than cluster processor size OR ticks <= 0\n";
        
        this->currentTickLog += error;
    }


}

void Scheduler::DisplayTickLog(){

    //print the current tick log to the console 
    cout << this->currentTickLog;

}