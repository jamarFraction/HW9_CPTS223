#include "JobQueue.h"

void JobQueue::InsertJob(Job &newJob)
{

    QueueNode *current = this->queueHead;

    QueueNode *previous;

    //create a new queueNode
    QueueNode *newNode;// = (QueueNode*)malloc(sizeof(QueueNode));

    newNode = CreateNode(newJob);


    //inserting into an empty list
    if (current == nullptr)
    {

        this->queueHead = newNode;
    }
    else
    {

        //Is the newNode's required ticks less than the current node's?
        if (newNode->remainingTicks < this->queueHead->remainingTicks)
        {

            //set the newNode's next to the node at the head of the list
            newNode->nextNode = this->queueHead;

            //set the new node as the head of the list
            this->queueHead = newNode;
        }
        else
        {

            //Keep looping while the new node's remaining ticks are greater than the current node's
            while (current != nullptr && newNode->remainingTicks >= current->remainingTicks)
            {

                //end of the queue case
                // if (current->nextNode == nullptr)
                // {

                //     //new node should be inserted at the end of the list

                //     break;
                // }
                // else
                // {

                    //update the pointers
                    previous = current;

                    current = current->nextNode;
                // }
            }

            //nullptr case, place newNode at the end of the list
            if (current == nullptr)
            {

                previous->nextNode = newNode;
            }
            else
            {

                //place the new node in between the previous and current nodes
                previous->nextNode = newNode;

                newNode->nextNode = current;
            }
        }
    }
}

QueueNode* JobQueue::CreateNode(Job &newJob){

    QueueNode *newNode = new QueueNode(newJob);
    
    return newNode;
}

bool JobQueue::IsEmpty(){

    if(this->queueHead == nullptr){

        return true;

    }

    return false;
}

QueueNode* JobQueue::GetHead(){

    return this->queueHead;

}

void JobQueue::SetHead(QueueNode *newHead){

    this->queueHead = newHead;

}