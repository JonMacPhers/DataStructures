
#ifndef _HASH_API_
#define _HASH_API_

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*************HASH TABLE API*************/
typedef struct treeNode
{
    void * data;
    int key;
    struct treeNode * left;
    struct treeNode * right;
    struct treeNode * parent;
}heapNode;

typedef struct sampleData
{
    char * name;   //perhaps a name?
    int * number;  
}DataObject;

typedef int HEAP_TYPE;

typedef struct Heap
{
    heapNode * heap;    // contains all of the heap nodes 
    HEAP_TYPE type;    // flag for choosing between min and max heap
    heapNode * lastPosition;    //optional element useful for finding where to insert the next value
    int (* compareData)(const void *first, const void *second);
    void (* deleteData)(void * toBeDeleted);
    void (* printData)(void * toBePrinted);
}Heap;

Heap * createHeap( char * htype,
        void (*destroyDataFP)(void *data),
        void (*printNodeFP)(void *toBePrinted),
        int (*compareFP)(const void *first, const void *second));

void deleteData( void *data );

void printData( void *toBePrinted );

int compareData(const void *first, const void *second);

void insertHeapNode( Heap * h, int key, void * data );

void lessGreater(Heap * h, heapNode * newNode, void * data, heapNode * temp);

void greaterLess(Heap * h, heapNode * newNode, void * data, heapNode * temp);

/********************************************************************************/
/********************************************************************************/

#endif
