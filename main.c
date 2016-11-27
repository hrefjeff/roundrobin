// Eileen Drass
// CS 420-01
// Programming Assignment - Round Robin clock algorithm implementation

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Round_Robin.h"

const int SIZE = 100;

//waitTime = clockTime - currentJob->arrivalTime - cpuTime;
int main(int argc, char** argv) 
{
  // Initializing clock variables...
  bool cpuOccupied = false; // Whether or not a job is in progress
  int  clockTime = 0; // Clock counter
  int  cpuTime = 0; 
  int  waitTime = 0; // how long for current job to wait in CPU
  int  timeQuantum = 10;
  int  timeLimit = timeQuantum;

  // Blocking out space for waiting queue, current job, and jobs...
  struct Node* currentJob; 
  memset(&currentJob, '\0', sizeof(currentJob));
  struct LinkedList waitingQueue;
  memset(&waitingQueue, '\0', sizeof(waitingQueue));
  struct Job record[SIZE];
  memset(&record, '\0', sizeof(record));

  readFile(record); 

  int elements = sizeof record / sizeof record[0];


  // Big clock loop  
  do {

      for(int i = 0; i < SIZE; i++)
      {
          if(clockTime == record[i].arrivalTime)
          {
              record[i].OG_serviceTime = record[i].serviceTime;
              enqueue(record[i], &waitingQueue);
          }
      }

      if((cpuOccupied == false) && (!isEmpty(&waitingQueue)))
      { 
          currentJob = dequeue(&waitingQueue);
          cpuTime = currentJob->job.serviceTime--;
          cpuOccupied = true;  
      }

      if (cpuOccupied == true)
      {
          timeLimit--;
          cpuTime--;

          // If the job is done
          if(cpuTime <= 0)
          {
              waitTime = clockTime - currentJob->job.arrivalTime - currentJob->job.OG_serviceTime;
              printf("Job %s is done! : arrived @ (%d) waited(%d) clock time(%d)\n", currentJob->job.name, currentJob->job.arrivalTime, waitTime,clockTime);
              cpuOccupied = false;
              timeLimit = timeQuantum;
              elements--; 
          }
          
          // trying to see if the job needs to go to the back of the line
          if((timeLimit <= 0) && (cpuOccupied == true) && !isEmpty(&waitingQueue))
          {
            timeLimit = timeQuantum;
            
            struct Job newJob;
            memset(&newJob, '\0', sizeof(newJob));
            for(int i = 0; i < 4; i++)
            {
              newJob.name[i] = currentJob->job.name[i]; 
            }
            newJob.arrivalTime = currentJob->job.arrivalTime;
            newJob.serviceTime = currentJob->job.serviceTime - timeQuantum;
            newJob.OG_serviceTime = currentJob->job.OG_serviceTime;
            newJob.priority = currentJob->job.priority;
            enqueue(newJob, &waitingQueue);
            
            cpuOccupied = false;
          
          } else if ((timeLimit <= 0) && isEmpty(&waitingQueue)) {

            timeLimit = timeQuantum;

          }
      }
        
      clockTime++;
     
  } while ((!isEmpty(&waitingQueue)) || (cpuOccupied == true) || (elements > 0)); 


  return (EXIT_SUCCESS);
}
