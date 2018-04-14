#ifndef JOB_H
#define JOB_H

#include <string>

using std::string;

class Job{

    public:
    
    Job(int passedJobID = 0, string passedJobDescription = "", int passed_n_procs = 0, int passed_n_ticks = 0){

        this->jobID = passedJobID;
        this->jobDescription = passedJobDescription;
        this->n_procs = passed_n_procs;
        this->n_ticks = passed_n_ticks;
    }

    int GetJobID(){
        return jobID;
    }

    string GetJobDescription(){
        return jobDescription;
    }

    int Get_N_Procs(){
        return n_procs;
    }

    int Get_N_Ticks(){
        return n_ticks;
    }

    private:

    int jobID;

    string jobDescription;

    int n_procs;

    int n_ticks;

};

#endif