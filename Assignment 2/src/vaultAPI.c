#include <ncurses.h>
#include "vaultAPI.h"
#include <string.h>
/*************HASH TABLE API*************/

void printData(void *toBePrinted)
{
	//DataObject * data;
    if(toBePrinted!=NULL)
    {   
    	//data = (DataObject *)toBePrinted;
        //printf("%s: # %ld\n", data->stringElement, data->numberElement);
    }
    return;
}
void deleteData(void *data)
{
	//notice the casting to myDataT in order to access the string element
	//free(((DataObject *)data)->stringElement);
  	free((DataObject *)data);
}

int hashFunction(int tableSize, char * key)
{/* Take a key and do something to it to get an index */
	int index = 0;
	index = strlen(key)%tableSize;
	return index;
}
HTable *createTable(int tableSize, int (*hashFunction)(int tableSize, char * key), void (*deleteFunction)(void *toBeDeleted), void (*printFunction)(void *toBePrinted))
{
	//New Hash Table
	HTable* hPtr = NULL;

	if(tableSize < 1) return NULL;

	/* Allocate the table itself. */
	if(( hPtr = malloc(sizeof( HTable ))) == NULL )
	{
		return NULL;
	}
	/* Allocate pointers to the head nodes. */
	if( ( hPtr->table = malloc( sizeof( hashNode * ) * tableSize ) ) == NULL )
	{
		return NULL;
	}
	hPtr->tableSize = tableSize;
	//Set the function tables to the functions passed in
	hPtr->hashFunction = hashFunction;
	hPtr->deleteData = deleteFunction;
	hPtr->printData = printFunction;
	return hPtr;
}
hashNode *initializeNode(char * key, void *data)
{
	if (data != NULL)
	{
		hashNode* node = malloc(sizeof(hashNode));
		node->data = malloc(sizeof(void*));
		node->key = malloc(sizeof(char)*strlen(key)+1);
		node->key = key;
		node->next = malloc(sizeof(hashNode));
	
		if ((node->data!=NULL)&&(node->next!=NULL))
		{
			node->data = data;
			node->next = NULL;
			return node;
		}
		else 
		{
			free(node->next);
			free(node->data);
			free(node);
			return NULL;
		}
	}
	return NULL;
}/*
int destroyTable( HTable* htable )
{
	int i = 0;
	while(i < htable->tableSize)
	{	printf("shit 1\n\n");
		hashNode* temp = htable->table[i];
		printf("shit 2\n\n");
		while(temp != NULL)
		{printf("shit 3\n\n");
			hashNode* tempDeleteNode = temp;
			temp = htable->table[i];
			printf("shit whaaaat\n\n");
			htable->deleteData((DataObject*)tempDeleteNode->data);
			printf("shit whaaaat\n\n");
			htable->deleteData((hashNode*)tempDeleteNode);
			i++;
		}
		i++;
	}
	printf("shit whaaaat\n\n");
	htable->deleteData(htable->table);
	htable->deleteData(htable);
	printf("\n\n\n******* TABLE TERMINATED *******\n\n\n");
	return 0;
}*/
void destroyTable (HTable *hashTable)
{
	hashNode* tmpPtr = NULL;

	if (hashTable == NULL)
	{	
		return;
	}
	if ((hashTable != NULL)&&(hashTable->table == NULL))
	{
		free(hashTable);
		return;
	}
	if ((hashTable != NULL)&&(hashTable->table != NULL))
	{
		int length = 0;
		for (length = 0; length<hashTable->tableSize; length++)
		{
			if (hashTable->table[length] == NULL)
			{
				free(hashTable->table[length]);
			}
			if (hashTable->table[length] != NULL)
			{
				int j = 0;
				tmpPtr = hashTable->table[j];
				while (tmpPtr != NULL && j < hashTable->tableSize)
				{
					printf("Table Destroyed Successfully\n");
					tmpPtr = hashTable->table[j];
					hashTable->deleteData(tmpPtr->data);
					free(tmpPtr);
					j++;
				}
					hashTable->deleteData(tmpPtr->data);
					printf("Table Destroyed Successfully");
					free(tmpPtr);
			}
		}
		printf("Table Destroyed Successfully");
		free(hashTable);
		printf("Table Destroyed Successfully");
		return;
	}			
}
int insertData( HTable * htable, char * key, void * toBeAdded, int collisionCounter )
{   
    if(htable != NULL)
    {
        hashNode* newData = initializeNode(key, toBeAdded);
        int index = htable->hashFunction(htable->tableSize, key);
        if(htable->table[index] != NULL)
        {   // Check the collision list first element, else check the rest
        	int i = 1;
        	if(htable->table[i] == NULL)
        	{
				htable->table[i] = newData;
        	}
        	if(htable->table[i] != NULL)
	    	{
	    		collisionCounter++;
	    		printw("\nCollsion Counter: %d\n\n", collisionCounter);
	    		return collisionCounter;
	    	}
        	while(htable->table[i] != NULL && i < htable->tableSize)
    		{
    			i++;
    		}	
    		newData->next = htable->table[i+1];	
	    	htable->table[i] = newData;
        }	
        else 
        {
        	newData->next = htable->table[index+1];
        	htable->table[index] = newData;
        }
    }   
    return collisionCounter;
}/*
void removeData(HTable* htable, int key )
{
    if( htable != NULL)
    {
        int index = htable->hashFunction(htable->tableSize, key);   
        if(htable->table[index] != NULL) 
    	{
            hashNode* dPtr = htable->table[index];
            hashNode* prev = NULL;
            while(dPtr->key != key)
            {
                prev = dPtr;
                dPtr = dPtr->next;
            }
            if(dPtr->key == key)
            {
                if(prev == NULL) 
                {    // Head of the list is removed
                    htable->table[index]->next = dPtr->next;
                    free(dPtr);
                    if(htable->table[index] == NULL)
                    {
                        free(htable->table[index]);
                    }
                }
                else
                {
                    prev->next = dPtr->next; 
                    free(dPtr);
                }
            }
        }
    }
}*/
void removeData (HTable *hashTable, char * key)
{	
	if (hashTable == NULL)
	{
		return;
	}
	int index = hashTable->hashFunction(hashTable->tableSize, key);
	
	if (hashTable->table[index] == NULL)
	{
		return;
	}
	if (hashTable->table[index] != NULL)
	{
		hashNode* current = NULL;
		hashNode* nextr = NULL;
		hashNode* prev = NULL;
		
		current = hashTable->table[index];
		nextr = current->next;
		
		while (nextr != NULL)
		{
			if (current->key == key)
			{
				if (current->next == NULL)
				{
					hashTable->deleteData(current->data);
					free(current);
					printw("Data Deleted\n\n");
					return;
				}
				if ((current!=NULL)&&(prev==NULL)&&(nextr!=NULL))
				{
					hashTable->table[index] = nextr;
					hashTable->deleteData(current->data);
					free(current);
					printw("Data Deleted\n\n");
					return;
				}
				// between two items
				if ((prev!=NULL)&&(current!=NULL)&&(nextr!=NULL))
				{
					prev->next = nextr;
					hashTable->deleteData(current->data);
					free(current);
					printw("Data Deleted\n\n");
					return;
				}
			}
			prev = current;
			current = nextr;
			nextr = current->next;
		}
		if (current->next == NULL)
		{
			hashTable->deleteData(current->data);
			free(current);
			printw("Data Deleted\n\n");
			return;
		}
	}
}
void* lookupData(HTable* htable, char * key )
{
    if(htable != NULL)
    {
        int index = htable->hashFunction( htable->tableSize, key );

        if(htable->table[index] == NULL)
        {
            return NULL;
        }
        hashNode * temp = htable->table[index]; 
        int loop = 1;
        while( loop == 1 )
        {
        	if(strcmp(temp->key, key) == 0)
            {
             	loop = 0;
             	return temp->data;
            }
            temp = temp->next;
    	}
    	printf("END OF TABLE: DATA NOT FOUND\n");
    }   
    return NULL;
}
/*************LINKED LIST API*************/
int compare (const void* compare1, const void* compare2)
{
	/* compare 1 is new element, compare 2 is list element */
	if (compare1 > compare2)
	{
		return 1;
	}
	if (compare1 == compare2)
	{
		return 0;
	}
	if (compare1 < compare2)
	{
		return -1;
	}
	return 0;
}
List *initializeCollisionList(void (*printFunction)(void *toBePrinted),void (*deleteFunction)(void *toBeDeleted),int (*compareFunction)(const void *first,const void *second))
{
	//New List pointer
	List* lPtr;
	lPtr = malloc(sizeof(struct listHead));
	
	//Check for creation OK!
	if (lPtr == NULL)
		return NULL;
		
	//malloc the head pointer
	lPtr->head = malloc(sizeof(hashNode*));
	lPtr->tail = malloc(sizeof(hashNode*));
	lPtr->head = NULL;
	lPtr->tail = NULL;

	
	//Set the function pointers to the functions passed in
	lPtr->printData = printFunction;
	lPtr->deleteData = deleteFunction;
	lPtr->compare = compareFunction;
	return lPtr;
}
void printTable(HTable * htable)
{
	if (htable == NULL)
	{
		printf("NULL");
		return;
	}
	else if ((htable != NULL))
	{
		int i = 0;
		hashNode* cPtr = NULL;
		cPtr = htable->table[0];
		while(i<htable->tableSize)
		{
			if(cPtr != NULL)
			{
				htable->printData(cPtr->data);
			}
			cPtr = cPtr->next;
			i++;
		}
	}
	printf("\n\n");
}
/*
void insertFront(List *list, void *toBeAdded)
{
	if (list == NULL)
	{
		return;
	}
	if (list->head == NULL)
	{
		listNode* newNode = NULL;
		newNode = initializeListNode(toBeAdded);
		list->head = newNode;
		list->tail = newNode;
		return;
	}
	if (list->head!=NULL)
	{
		listNode* newNode = NULL;
		newNode = initializeListNode(toBeAdded);
		listNode* tmpptr = list->head; //pointing at the old first node
		list->head = newNode;		//head of list to new node
		newNode->next = tmpptr;		//newnodes next ptr is the old head
		tmpptr->previous = newNode;
		return;
	}
	else
	{
		return;
	}
}
void printForward(List *list)
{
	if (list == NULL)
	{
		return;
	}
	if ((list != NULL) && (list->head != NULL))
	{
		listNode* tempPtr = list->head;
		do
		{
			list->printData(tempPtr->data);
			printf(", ");
			tempPtr = tempPtr->next;
		}
		while(tempPtr->next!= NULL);
		
		list->printData(tempPtr->data);
		tempPtr = tempPtr->next;
	}
	printf("\n");
}*/