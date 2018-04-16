#include "Job.h"

struct QueueNode
{

  public:
    QueueNode() {}

    QueueNode(Job &newJob)
    {

        nodeJob = newJob;

        this->nextNode = nullptr;

        this->remainingTicks = newJob.Get_N_Ticks();
    }

    Job nodeJob;

    int remainingTicks;

    QueueNode *nextNode;
};