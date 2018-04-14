#include "Scheduler.h"

Scheduler::Scheduler(int numberOfProcessors){

    //Init the cluster processor size and the number of free processors
    this->processorCount = numberOfProcessors;
    this->freeProcessors = numberOfProcessors;
}

Scheduler::~Scheduler(){}


void Scheduler::RunScheduler(istream &inputFile){

    system("clear");

    bool terminate = false;

    while(!terminate){

        this->currentTickLog = "";

        this->numberOfTicks += 1;

        cout << "Tick #" << this->numberOfTicks << endl;

        //Perform the tick
        terminate = Tick(inputFile);

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

bool Scheduler::Tick(istream &inputFile){

    //an istream will have a gcount of 0 if a file
    std::streamsize size = inputFile.gcount();

    if(size == 0){

        //user input, NOT reading from a file
        //perform the text file line read and job creation

        if(!inputFile.eof()){

            this->AutoLine_JobCreate(inputFile);

        }
        
        
    }else{

        //perform the manual line entry and job creation
        //exit command from user will end the program and set terminate to true
        bool terminate = this->ManualLine_JobCreate();

        //terminate this tick, susequently terminating the program
        if(terminate == true){

            return true;
        }
    }
    
    //Check for the running jobs queue being empty
    if(!this->runningJobQueue.IsEmpty()){

        //decrement the remaining ticks for each Job in the running queue
        DecrementTimer();

        //release any jobs and processors associated with them if neccessary
        ReleaseProcs();

    }

    //check for a non-empty waiting queue
    if(!this->waitQueue.isEmpty()){

        //Process the wait queue
        ProcessWaitQueue();
    }
  
    return false;
}

void Scheduler::AutoLine_JobCreate(istream &inputFile){

    //read a line from the file
    string line = "";

    getline(inputFile, line);

    //verify that this line is not a NULL job
    if(line.substr(0, line.find(" ")) != "NULL"){

        Job newJob = CreateJob(line);

        //attempt to insert the job into the waiting queue
        InsertJob(newJob);  

        //add this event to the current tick log
        this->currentTickLog.append("Job: " + to_string(newJob.GetJobID()) + "  " + newJob.GetJobDescription() + 
        "  " + to_string(newJob.Get_N_Procs()) + "  " + to_string(newJob.Get_N_Ticks()) + " added to waiting job queue\n");

    }
}

bool Scheduler::ManualLine_JobCreate(){

    string userInput = "";

    system("clear");
    cout << "Please enter a new job with values separated by spaces (ex. job_description n_procs n_ticks): ";
    //cin.ignore();
    getline(cin, userInput);

    //user wants to create a new job
    if(userInput != "NULL" && userInput != "exit"){

        //create a job with the passed string
        Job newJob = CreateJob(userInput);

        //attempt to insert the job into the waiting queue
        InsertJob(newJob);

        //add this event to the current tick log
        this->currentTickLog.append("Job: " + to_string(newJob.GetJobID()) + "  " + newJob.GetJobDescription() + 
        "  " + to_string(newJob.Get_N_Procs()) + "  " + to_string(newJob.Get_N_Ticks()) + " added to waiting job queue\n");
    }

    if(userInput == "exit"){

        //true return will end the program 
        return true;
    }

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

Job Scheduler::FindShortest(){

    //return a copy of the job in the wait queue requiring the least number of processors
    return this->waitQueue.findMin();

}

bool Scheduler::CheckAvailability(Job &minJob) const{

    //Do we have enough free processors in the pool?
    if(this->freeProcessors >= minJob.Get_N_Procs()){

        return true;

    }

    return false;
}

void Scheduler::DeleteShortest(){

    //remove the job requiring the least number of processors from the queue
    this->waitQueue.deleteMin();
}

void Scheduler::RunJob(Job &newJob){

    //insert the job into the running job queue
    this->runningJobQueue.InsertJob(newJob);

    //add this event to the current tick log
    this->currentTickLog.append("Job: " + to_string(newJob.GetJobID()) + "  " + newJob.GetJobDescription() + 
    "  " + to_string(newJob.Get_N_Procs()) + "  " + to_string(newJob.Get_N_Ticks()) + " added to running job queue\n");

}

void Scheduler::ProcessWaitQueue(){

    do{

        //find the job requiring the least amout of proccessors
        Job minJob = FindShortest();

        //are there sufficeint free processors to handle the minJob?
        if (CheckAvailability(minJob))
        {

            //Remove the minJob from the wait queue
            DeleteShortest();

            //decrement the number of free processors by how many this new job requires
            this->freeProcessors -= minJob.Get_N_Procs();

            //insert the job into the running job queue
            RunJob(minJob);

            //update minJob for loop control
            if (!this->waitQueue.isEmpty())
            {

                minJob = this->waitQueue.findMin();

                //if the next job in the wait queue requires more processors than available, exit the loop
                if (minJob.Get_N_Procs() > this->freeProcessors)
                {

                    break;
                }
            }
        }else{

            break;
        }
    } while (!this->waitQueue.isEmpty());
}

void Scheduler::DecrementTimer(){

    //get the head of the queue
    QueueNode *current = this->runningJobQueue.GetHead();

    //iterate over each node and decrement its number of remaining ticks by 1
    while(current != nullptr){

        current->remainingTicks -= 1;

        current = current->nextNode;
    }
}

void Scheduler::ReleaseProcs(){

    if(this->runningJobQueue.GetHead()->remainingTicks == 0){

        QueueNode *current = this->runningJobQueue.GetHead();

        //Loop until the head of the queue's remaining ticks is not zero
        while(current != nullptr && current->remainingTicks == 0){

            QueueNode *toDelete = current;

            current = current->nextNode;

            this->runningJobQueue.SetHead(current);

            //add this event to the current tick log
            this->currentTickLog.append("Job: " + to_string(toDelete->nodeJob.GetJobID()) + "  " + toDelete->nodeJob.GetJobDescription() + 
            "  " + to_string(toDelete->nodeJob.Get_N_Procs()) + "  " + to_string(toDelete->nodeJob.Get_N_Ticks()) + " complete. Removing from running queue\n");

            //Release the processors used for this job back into the free pool
            this->freeProcessors += toDelete->nodeJob.Get_N_Procs();

            free(toDelete);
        }

    }

}