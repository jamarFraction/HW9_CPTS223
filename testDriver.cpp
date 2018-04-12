#include <iostream>
#include <fstream>


#include "Scheduler.h"

using namespace std;
using std::ifstream;

int main(void){

    int user_input;

    
    do{
    
        system("clear");
        cout << "Please enter the number of processors to be used in this cluster: ";
        cin >> user_input;
        //user_input = (int)user_input;
        

    }while(user_input <= 0);

    //create a new scheduler instance
    Scheduler newScheduler = Scheduler(user_input);

    
    //Init the job list file
    ifstream input("input.txt");

    //check for the file being open before proceeding
    if(input.is_open()){

        //run the scheduler.. for test inputs
        newScheduler.RunScheduler(input);
        //newScheduler.RunScheduler();
        

    }else{

        //clear the screen and display the file error
        system("clear");
        cout << "Error opening/locating file, terminating program" << endl;
    }

    return 0;
}