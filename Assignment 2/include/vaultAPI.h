
#ifndef _HASH_API_
#define _HASH_API_

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*************HASH TABLE API*************/
typedef struct listNode{
    void * data;
    char * key;
    struct listNode * next;
}hashNode;

typedef struct sampleData
{
    char * systemDescriptor;   //perhaps a name?
    char * password;  
}DataObject;

typedef struct hashTable{
    int tableSize;
    hashNode ** table;
    int (* hashFunction)( int tableSize, char * key );
    void (* deleteData)(void * toBeDeleted);
    void (* printData)(void * toBePrinted);
}HTable;

HTable * parseFile(HTable * htable, FILE * ptr, int collisionCounter);

void printMessage2(char * s);

void printMessage1(char * s);

void moveTwoY();

int hashFunction( int tableSize, char * key );

HTable *createTable(int tableSize, int (*hashFunction)(int tableSize, char * key), void (*deleteFunction)(void *toBeDeleted), void (*printFunction)(void *toBePrinted));

hashNode *initializeNode(char * key, void *data);

int insertData( HTable * htable, char * key, void * toBeAdded, int collisionCounter);

void removeData(HTable* htable, char * key);

void* lookupData(HTable* htable, char * key);

void printData(void *toBePrinted);

void deleteData(void *deleteme);

void destroyTable( HTable* htable );

void fprintTable(HTable * htable, FILE * file);

/********************************************************************************/
/********************************************************************************/

#endif
