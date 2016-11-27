// Eileen Drass
// CS 420-01
// Programming Assignment - Round Robin clock algorithm implementation
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Round_Robin.h"


//------------------------------------------------------------------------------
// This function will add data to the queue. Its parameters includes the record
// which is being added to the queue and the queue itself. Because it should 
// not return anything, it is a void function.
void enqueue(struct Job record, struct LinkedList *queue)
{    
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node)); 


    for(int i = 0; i < 4; i++)
    {
       temp->name[i] = record.name[i]; 
    }

    temp->arrivalTime = record.arrivalTime;
    temp->serviceTime = record.serviceTime;
    temp->priority = record.priority;
 

    temp->next = NULL; 

 
    // If empty queue...    
    if((queue->front == NULL) && (queue->back == NULL))
    {
        queue->front = temp;
        queue->back = temp;
    }
        
    else
    {
        queue->back->next = temp;
        queue->back = temp;
    }

}

//------------------------------------------------------------------------------
// This function will delete an element from the queue. Its parameters include
// the queue in which a job will be deleted. 
struct Node *dequeue(struct LinkedList *queue)
{    
    struct Node* temp = queue->front;
    struct Node* recordInfo = temp; 
        
    if((queue->front == NULL)&& (queue->back == NULL)) 
    {
        //printf("Queue is Empty\n");
    }
        
    // If there is only one element in queue
    else if(queue->front == queue->back) 
    {
        queue->front = NULL;
        queue->back = NULL;
    }
        
    else 
    {
        queue->front = queue->back->next;
    }
        
    temp = temp->next;
    free(queue->front); 
    queue->front = temp;
    
    return recordInfo; 
        
    //printf("Dequeue'd \n");
}

//------------------------------------------------------------------------------
// This function will read input from a file. Its parameter includes the record
// array which the input will be stored into. 
void readFile(struct Job record[])
{    
    char fileName[100];
    FILE *filePtr;
    
  //  printf("Enter the name of the file you would like to open: ");
   // scanf("%100s", fileName); 
   // filePtr = fopen(fileName, "r"); 
    filePtr = fopen("jobs100.txt", "r"); 
    
    
    if(filePtr == NULL)
    {
        printf("Could not open file. \n");
    }
    
    
    else
    {
        // Storing items from file into an array of jobs.       
        for(int i = 0; i < 3; i++)
        {
            fscanf(filePtr, "%s %d %d %d", &record[i].name, 
                    &record[i].arrivalTime, &record[i].serviceTime, 
                    &record[i].priority);                        
        }
    }

    fclose(filePtr);
}

//------------------------------------------------------------------------------
// This function will output the jobs as they are completed to a file named 
// output.txt. 
void outputFile(struct Node* currentJob, int waitTime, int clockTime)
{
    FILE *filePtr; 
    
    filePtr = fopen("output.txt", "a");
    
    fprintf(filePtr, "%s %d %d %d", currentJob->name, currentJob->arrivalTime,  
             waitTime, clockTime);
    
    fprintf(filePtr, "\n");
    
    fclose(filePtr);
}

//------------------------------------------------------------------------------
// This function will tell whether the queue is empty or not. Its parameters
// include the queue. It will return a false if it is not empty or true if it
// is empty. 
bool isEmpty(struct LinkedList *queue)
{
    if ((queue->front == NULL) && (queue->back == NULL))
    {
        return true;
    }
    
    else
    {
        return false;
    }
}
//------------------------------------------------------------------------------
// This function will print the queue. Its parameters include the queue which
// needs to be printed.
void print_queue(struct LinkedList* queue)
{
    struct Node *ptr = queue->front;
    
    printf("\n");
    
    while(ptr != NULL)
    {
        printf("%s %d %d %d", ptr->name, ptr->arrivalTime, 
                  ptr->serviceTime, ptr->priority); 
        printf("\n");
        ptr = ptr->next;
    }
    
    return;
}


