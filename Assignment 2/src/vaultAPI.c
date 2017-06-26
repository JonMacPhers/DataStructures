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
	DataObject * temp = data;
	free(temp->systemDescriptor);
	free(temp->password);
	free(temp);
	temp = NULL;
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
	{printMessage2("Yayyyy");
		hashNode* node = NULL;
		printMessage2("whooops #111");
		node = malloc(sizeof(hashNode));
		printMessage2("whooops #1");
		node->data = malloc(sizeof(void*));
		printMessage2("whooops #2");
		node->key = malloc(sizeof(char)*strlen(key)+1);
		node->key = key;
		printMessage2("whooops #3");
		node->next = malloc(sizeof(hashNode));
		printMessage2("whooops #4");
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
	printMessage2("whooops");
	return NULL;
}
/*void destroyTable (HTable *hashTable)
{
	Node* tmpPTR = NULL;
	Node* tmpPTR2 = NULL;

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
		for (length = 0; length<hashTable->size; length++)
		{
			if (hashTable->table[length] == NULL)
			{
				free(hashTable->table[length]);
			}
			if (hashTable->table[length] != NULL)
			{
				tmpPTR = hashTable->table[length];
				while (tmpPTR->next != NULL)
				{
					tmpPTR2 = tmpPTR->next;
					hashTable->destroyData(tmpPTR->data);
					free(tmpPTR);
					tmpPTR = tmpPTR2;
					//printf("Inside while! \n");
				}
					hashTable->destroyData(tmpPTR->data);
					free(tmpPTR);
					//printf("Outside while!\n");
			}
		}
		free(hashTable);
		return;
	}			
} */
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
{   printMessage2("Whoops1");
    if(htable != NULL)
    {   printMessage2("Whoops2");
        hashNode* newData = NULL; 
        newData = initializeNode(key, toBeAdded);
        printMessage2("Whoops UMM"); 
        int index = htable->hashFunction(htable->tableSize, key);
        printMessage2("Whoops3");
        if(htable->table[index] != NULL)
        {   // Check the collision list first element, else check the rest
        	if(htable->table[index]->next == NULL)
        	{
				htable->table[index]->next = newData;
	    		collisionCounter++;
	    		int y_coordinate, x_coordinate;
	    		getyx(stdscr, y_coordinate, x_coordinate);
	    		mvwprintw (stdscr, y_coordinate, x_coordinate, "Collsion Counter:");
	    		getyx(stdscr, y_coordinate, x_coordinate);
	    		wmove(stdscr, y_coordinate, x_coordinate+1);
	    		printw ("%d", collisionCounter);
	    		wmove(stdscr, y_coordinate+2, 0);
	    		refresh();
	    		return collisionCounter;
        	}
        	else if(htable->table[index]->next != NULL)
	    	{
	    		hashNode * tempNode = htable->table[index]->next;
	    		while(tempNode->next != NULL)
	    		{
	    			tempNode = tempNode->next;
	    		}
    			tempNode = newData;
    			collisionCounter++;
	    		int y_coordinate, x_coordinate;
	    		getyx(stdscr, y_coordinate, x_coordinate);
	    		mvwprintw (stdscr, y_coordinate, x_coordinate, "Collsion Counter:");
	    		getyx(stdscr, y_coordinate, x_coordinate);
	    		wmove(stdscr, y_coordinate, x_coordinate+1);
	    		printw ("%d", collisionCounter);
	    		wmove(stdscr, y_coordinate+2, 0);
	    		refresh();
	    		return collisionCounter;
	    	}
        }
        else if(htable->table[index] == NULL)
        {printMessage2("Whoopsa");
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
/*void removeData (HTable *hashTable, int key)
{	
	if (hashTable == NULL)
	{
		return;
	}
	int index = hashTable->hashFunction(hashTable->size, key);
	
	if (hashTable->table[index] == NULL)
	{
		return;
	}
	if (hashTable->table[index] != NULL)
	{
		// otherwise search for element
		Node* current = NULL;
		Node* nextr = NULL;
		Node* prev = NULL;
		
		current = hashTable->table[index];
		nextr = current->next;
		
		while (nextr != NULL)
		{
			//found the element
			if (current->key == key)
			{
				//lone item or end of list
				if (current->next == NULL)
				{
					hashTable->destroyData(current->data);
					free(current);
					return;
				}
				//first element in two element list
				if ((current!=NULL)&&(prev==NULL)&&(nextr!=NULL))
				{
					hashTable->table[index] = nextr;
					hashTable->destroyData(current->data);
					free(current);
					return;
				}
				// sandwhiched between two items
				if ((prev!=NULL)&&(current!=NULL)&&(nextr!=NULL))
				{
					prev->next = nextr;
					hashTable->destroyData(current->data);
					free(current);
					return;
				}
			}
			prev = current;
			current = nextr;
			nextr = current->next;
		}
		if (current->next == NULL)
		{
			hashTable->destroyData(current->data);
			free(current);
			return;
		}
	}
} */
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
		nextr = hashTable->table[index]->next;

		hashTable->table[index] = NULL;
		
		while (nextr != NULL)
		{
			if (current->key == key)
			{
				if ((current!=NULL)&&(nextr!=NULL))
				{
					prev = current;
					current = nextr;
					nextr = current->next;
					hashTable->deleteData(prev->data);
					prev->data = NULL;
					free(prev->key);
					prev->key = NULL;
					free(prev);
					prev = NULL;
				}
			}
		}
		if (nextr == NULL)
		{
			hashTable->deleteData(current->data);
			current->data = NULL;
			free(current->key);
			current->key = NULL;
			free(current);
			current = NULL;
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
            printMessage1("DATA NOT FOUND");
        }
        hashNode * temp = htable->table[index]->next;
		if(temp != NULL && (strcmp(temp->key, key) == 0))
		{	
			int Counter = 1;
			DataObject * CollisionData = NULL;
			CollisionData = malloc(sizeof(DataObject));
			while(temp != NULL && (strcmp(temp->key, key) == 0))
			{
				CollisionData = temp->data;
				printw("Collision # %d Saved Password-> %s", Counter, CollisionData->password);
				moveTwoY();
				moveTwoY();
				Counter++;
				temp = temp->next;
			}
		}
		if(strcmp(htable->table[index]->key, key) == 0)
        {
         	return htable->table[index]->data;
        }
    }
    else if(htable == NULL)
    {   
    	printMessage1("No Table");
    }
    return NULL;
}
void printMessage2(char * s)
{
    int x, y;
    getyx(stdscr, y, x);
    if((x == 0) && (y == 0))
    {
  		wprintw (stdscr, s);
  		wmove(stdscr, y+2, 0);
    } 
    else
    {   
    	wmove(stdscr, y+1, 0);
    	getyx(stdscr, y, x);
	    mvwprintw (stdscr, y, x, s);
	    wmove(stdscr, y+2, 0);
	    refresh();
	}
}
void printMessage1(char * s)
{
    int x, y;
    getyx(stdscr, y, x);
    if((x == 0) && (y == 0))
    {
  		wprintw (stdscr, s);
  		wmove(stdscr, y+1, 0);
    } 
    else
    {  
	    mvwprintw (stdscr, y, x, s);
	    wmove(stdscr, y+1, 0);
	    refresh();
	}
}
void moveTwoY()
{
	int x_coordinate, y_coordinate;
	getyx(stdscr, y_coordinate, x_coordinate);
	move(y_coordinate+1, x_coordinate - x_coordinate);
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