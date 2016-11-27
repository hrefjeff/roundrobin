// Eileen Drass
// CS 420-01
// Programming Assignment - Round Robin clock algorithm implementation

#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "Round_Robin.h"

//waitTime = clockTime - currentJob->arrivalTime - cpuTime;
int main(int argc, char** argv) 
{
    // Initializing clock variables...
    bool cpuOccupied = false; // Whether or not a job is in progress
    int  clockTime = 0; // Clock counter
    int  cpuTime = 0; 
    //int  cpuCount = 0; // number of jobs in CPU 
    int  waitTime = 0; // how long for current job to wait in CPU
    int  timeQuantum = 10;
    int  timeLimit = timeQuantum;
    
    
    // Blocking out space for waiting queue, current job, and jobs...
    struct Node* currentJob; 
    memset(&currentJob, '\0', sizeof(currentJob));
    
    struct LinkedList waitingQueue;
    memset(&waitingQueue, '\0', sizeof(waitingQueue));
    
    struct Job record[3];
    memset(&record, '\0', sizeof(record));

    // Read input from the file
    readFile(record); 

    // Number of elements in array of jobs
    int elements = sizeof record / sizeof record[0];
 
    
    // Big clock loop  
    do {

        if (cpuOccupied == true)
        {
            timeLimit--;
            
            // trying to see if the job needs to go to the back of the line
            if(timeLimit == 0)
            {
              timeLimit = timeQuantum;
              
              //printf("Job returning to waiting queue: %s %d", currentJob->name, currentJob->serviceTime);
              //printf("\n");
              
              // create a job 
              struct Job newJob; 
              memset(&newJob, '\0', sizeof(newJob));
              
              for(int i = 0; i < 4; i++)
              {
                newJob.name[i] = currentJob->Job->name[i]; 
              }
              
              newJob.arrivalTime = currentJob->arrivalTime;
              newJob.serviceTime = currentJob->serviceTime - timeQuantum;
              printf("Service Time: %d \n", newJob.serviceTime);
              newJob.priority = currentJob->priority;
 
              enqueue(newJob, &waitingQueue); 
              cpuOccupied = false;
            }
            
            // If the job is done
            if(cpuTime == 0)
            {
                printf("Testing: %s %d %d %d", currentJob->name, clockTime, currentJob->arrivalTime, currentJob->serviceTime); 
                printf("\n");
                waitTime = clockTime - currentJob->arrivalTime - currentJob->serviceTime;
                printf("%s %d %d %d", currentJob->name, currentJob->arrivalTime, waitTime, 
                        clockTime); 
                printf("\n");
                cpuOccupied = false; 
                elements--; 
            }    
        
        }
        
        for(int i = 0; i < 3; i++)
        {
            if(clockTime == record[i].arrivalTime)
            {
                enqueue(record[i], &waitingQueue);
               // elements--;
            }
        }
        
        if (cpuOccupied == true)
        {
            cpuTime--; 
        }
        
        if((cpuOccupied == false) && (!isEmpty(&waitingQueue)))
        { 
            currentJob = dequeue(&waitingQueue);
            cpuTime = currentJob->serviceTime--;
            cpuOccupied = true;  
        }
        
          
        clockTime++; 
       
    } while ((!isEmpty(&waitingQueue)) || (cpuOccupied == true) || (elements > 0)); 

 
    return (EXIT_SUCCESS);
}
