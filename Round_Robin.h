// Eileen Drass
// CS 420-01
// Programming Assignment - Round Robin clock algorithm implementation

#ifndef ROUND_ROBIN_H
#define ROUND_ROBIN_H


typedef int bool;
#define true 1
#define false 0

struct Job 
{
    char name[4];
    int arrivalTime;
    int serviceTime;
    int priority;

};

struct Node 
{
    struct Job job; 
    struct Node* next;
};

struct LinkedList 
{
    struct Node* front;
    struct Node* back;
};


void enqueue(struct Job record, struct LinkedList *queue);
struct Node *dequeue(struct LinkedList *queue);
void readFile(struct Job record[]);
void outputFile(struct Node* currentJob, int waitTime, int clockTime);
void print_queue(struct LinkedList* queue);
bool isEmpty(struct LinkedList *queue);

#endif /* ROUND_ROBIN_H */

