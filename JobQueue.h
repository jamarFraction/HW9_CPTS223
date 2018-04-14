#ifndef JOBQUEUE_H
#define JOBQUEUE_H

#include "QueueNode.h"
#include "Job.h"

class JobQueue{

    public:

    JobQueue(){

        this->queueHead = nullptr;
        
    }

    void InsertJob(Job &newJob);

    bool IsEmpty();

    QueueNode* GetHead();

    void SetHead(QueueNode *newHead);


    private:

    QueueNode *queueHead;

    QueueNode* CreateNode(Job &newJob);
};

#endif