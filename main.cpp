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
        
    }while(user_input <= 0);

    //create a new scheduler instance
    Scheduler newScheduler = Scheduler(user_input);

    //Run the scheduler program... for user-input
    newScheduler.RunScheduler();

    return 0;
}