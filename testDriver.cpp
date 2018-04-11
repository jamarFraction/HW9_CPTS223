#include <iostream>
#include <fstream>


#include "Scheduler.h"

using namespace std;
using std::ifstream;

int main(void){

    int p;

    do{
    
        system("clear");
        cout << "Please enter the number of processors to be used in this cluster: ";
        cin >> p;
        

    }while(p <= 0);

    //create a new scheduler instance
    Scheduler newScheduler = Scheduler(p);

    //Init the job list file
    ifstream input("input.txt");

    //check for the file being open before proceeding
    if(input.is_open()){

        //run the scheduler
        newScheduler.RunScheduler(input);
        

    }else{

        //clear the screen and display the file error
        system("clear");
        cout << "Error opening/locating file, terminating program" << endl;
    }

    return 0;
}



// BinaryHeap<int> newHeap = BinaryHeap<int>(1);

    // newHeap.insert(24);

    // newHeap.insert(6);

    // newHeap.insert(12);

    

    // cout << newHeap.findMin() << endl;