
#ifndef _HASH_API_
#define _HASH_API_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
/*************HASH TABLE API*************/
typedef struct listNode{
    void *data;
    int key;
    struct listNode *next;
}hashNode;

typedef struct hashTable{
    int tableSize;
    hashNode** table;
    int (*hashFunction)( int tableSize, int key );
    void (*deleteData)(void *toBeDeleted);
    void (*printData)(void *toBePrinted);
}HTable;

typedef struct StudentInfo{
	char* firstName;
	char* lastName;
	char* major;
}Student;

int hashFunction( int tableSize, int key );

HTable *createTable(int tableSize, int (*hashFunction)(int tableSize, int key), void (*deleteFunction)(void *toBeDeleted), void (*printFunction)(void *toBePrinted));

hashNode *initializeNode(int key, void *data);

void insertData( HTable * htable, int key, void * toBeAdded );

void printData(void *printCar);

void deleteData(void *deleteme);

int hashFunction(int tableSize, int key);

/*************LINKED LIST API*************/

int compare (const void* compare1, const void* compare2);

typedef struct listHead{
    hashNode *head;
    hashNode *tail;
    void (*deleteData)(void *toBeDeleted);
    int (*compare)(const void *first,const void *second);
    void (*printData)(void *toBePrinted);
}List;

List *initializeList(void (*printFunction)(void *toBePrinted),void (*deleteFunction)(void *toBeDeleted),int (*compareFunction)(const void *first,const void *second));

hashNode *initializeListNode(void *data);

//void insertFront(List *list, void *toBeAdded);

//void printForward(List *list);

#endif
