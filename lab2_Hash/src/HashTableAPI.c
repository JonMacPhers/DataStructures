#include "../include/HashTableAPI.h"
/*************HASH TABLE API*************/
void printData(void *printCar)
{
	return ;
}
void deleteData(void *deleteme)
{
	free(deleteme);
	return;
}
int hashFunction(int tableSize, int key)
{/* Take a key and do something to it to get an index */
	int index = 0;
	index = (key*2654435761)%(2^32);
	return index;
}
HTable *createTable(int tableSize, int (*hashFunction)(int tableSize, int key), void (*deleteFunction)(void *toBeDeleted), void (*printFunction)(void *toBePrinted))
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
hashNode *initializeNode(int key, void *data)
{
	if (data != NULL)
	{
		hashNode* node = malloc(sizeof(hashNode*));
		node->data = malloc(sizeof(void*));
		node->key = key;
		node->next = malloc(sizeof(hashNode*));
	
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
}
int destroyTable( HTable* htable )
{
	int i;
	for(i = 0; i < htable->tableSize; i++)
	{	
		hashNode* temp = htable->table[i];
		while(temp != NULL)
		{
			hashNode* tempDeleteNode = temp;
			temp = temp->next;
			free(tempDeleteNode->data);
			free(tempDeleteNode);
		}
	}
	free(htable->table);
	free(htable);
	return 0;
}

int insertData( HTable * htable, int key, void * toBeAdded, int collisionCounter )
{   
    if(htable != NULL)
    {
        hashNode* newData = initializeNode(key, toBeAdded);
        int index = htable->hashFunction(htable->tableSize, key);
        if(htable->table[index] != NULL)
        {   // Check the collision list first element, else check the rest
        	int i = 1;
        	if(htable->table[i] == NULL)
        	{printf("whoops\n\n");
				htable->table[i] = newData;
        	}
        	if(htable->table[i] != NULL)
	    	{
	    		collisionCounter++;
	    		printf("Collsion Counter: %d\n\n", collisionCounter);
	    		return collisionCounter;
	    	}
        	while(htable->table[i] != NULL && i < htable->tableSize)
    		{
    			i++;
    		}		
	    	htable->table[i] = newData;
        }	
        else if(htable->table[index] == NULL)
        {
        	htable->table[index] = newData;
        } 
    }   
    return collisionCounter;
}
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
}
void* lookupData(HTable* htable, int key )
{
    if(htable != NULL)
    {
        int index = htable->hashFunction( htable->tableSize, key );

        if(htable->table[index] == NULL)
        {printf("okay WHAT\n");
            return NULL;
        }
        hashNode * temp = htable->table[index]; 
        while( temp != NULL )
        {   if(temp->key == key)
            {  printf("okay DATA\n");
             	return temp->data;
            }
            temp = temp->next;
    	}printf("okay END\n");
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