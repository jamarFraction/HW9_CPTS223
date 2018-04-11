#include <string>

using std::string;

class Job{

    Job(int passedJobID, string passedJobDescription, int passed_n_procs, int passed_n_ticks){

        this->jobID = passedJobID;
        this->jobDescription = passedJobDescription;
        this->n_procs = passed_n_procs;
        this->n_ticks = passed_n_ticks;
    }

    private:

    int jobID;

    string jobDescription;

    int n_procs;

    int n_ticks;

};