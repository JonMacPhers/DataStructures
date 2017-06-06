/*
 * @file LinkedQueueAPI.h
 * @author Jonathan MacPherson
 * @date June 6th, 2017
 * @brief File containing the function definitions of a 4-Way Stop Simulation
 */

#ifndef _Queue_API_
#define _Queue_API_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printC(void *printme);
void printI(void *printme);
void deleteMe (void*);
int comparefunc (const void*, const void*);

/**
*Car of a linked Queue. This Queue is doubly linked, meaning that it has points to both the Car immediately in front 
of it, as well as the Car immediately behind it.
**/
typedef struct queueCar{
    void *direction;
    void *path;
    void *clock;
    struct queueCar *previous;
    struct queueCar *next;
}Car;

/**
 *Dummy Front of the Queue. Contains no actual data on it beyond a pointer to the front and end of the Queue.
 **/
typedef struct queueCommander{
    Car* Front;
    Car* Back;
    void (*deleteData)(void *toBeDeleted);
    void (*printI)(void *intPrinted);
    void (*printC)(void *charPrinted);
}Queue;

/*
typedef struct storageCommander{
    Stode* Front;
    Stode* Back;
    void (*deleteData)(void *toBeDeleted);
    void (*printI)(void *intPrinted);
    void (*printC)(void *charPrinted);
}Store;

typedef struct storageNode{
    void *direction;
    void *path;
    void *clock;
    struct storageNode *previous;
    struct storageNode *next;
}Stode;
*/
Queue *initializeQueue(void (*printCharFunction)(void *charPrinted),void (*deleteFunction)(void *toBeDeleted),void (*printIntFunction)(void *intPrinted));

//Store *initializeStore(void (*printCharFunction)(void *charPrinted),void (*deleteFunction)(void *toBeDeleted),void (*printIntFunction)(void *intPrinted));

Car *initializeCar(void *direction, void *path, void *clock);

Queue *enqueue(Queue *queue, void *toBeAdded1, void *toBeAdded2, void*toBeAdded3);

void *Front(Queue *queue);

void printFrontToBack(Queue *queue);

void Simulation(char *simData, int length);

void Simulation(char *simData, int length);
//Queue *memory, 
Queue* parseFile(Queue *queue, char *simData, int length);

#endif
