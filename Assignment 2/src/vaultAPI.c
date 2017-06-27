#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "vaultAPI.h"
#include <string.h>
/*************HASH TABLE API*************/
/**This is used for all the functionality for the hash table*/

/**
Prints the data
*/
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
/**
Helper function to delete the data from a node
*/
void deleteData(void *data)
{
	DataObject * temp = data;
	free(temp->systemDescriptor);
	free(temp->password);
	free(temp);
	temp = NULL;
}
/**
Takes the key and generates an index for it
*/
int hashFunction(int tableSize, char * key)
{
	int index = 0;
	index = (int)strtol(key, NULL, 10)%tableSize;
	return index;
}
/**
Creates and initializes the table
*/
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
/**
Creates and initializes a node
*/
hashNode *initializeNode(char * key, void *data)
{
	if (data != NULL)
	{
		hashNode* node = NULL;
		node = (hashNode *)malloc(sizeof(hashNode));
		node->data = malloc(sizeof(void*));
		node->key = (char *)malloc(sizeof(char)*strlen(key)+1);
		node->key = key;
		node->next = (hashNode *)malloc(sizeof(hashNode));
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
/**
Frees all data in the table and frees the memory
*/
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
/**
Inserts the data into the table
*/
int insertData( HTable * htable, char * key, void * toBeAdded, int collisionCounter )
{   
    if(htable != NULL)
    {   
        hashNode* newData = NULL; 
        newData = initializeNode(key, toBeAdded); 
        int index = htable->hashFunction(htable->tableSize, key);
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
	    		hashNode * tempNode = htable->table[index];
	    		while(tempNode->next != NULL)
	    		{
	    			tempNode = tempNode->next;
	    		}
    			tempNode->next = newData;
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
        {
        	htable->table[index] = newData;
        }
    }   
    return collisionCounter;
}
/**
Removes the data from the table
*/
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
/**
Parses the file into easy to manipulate data which is then put inside the table
*/
HTable * parseFile(HTable * htable, FILE * ptr, int collisionCounter)
{
	int length = 0;
	fseek(ptr, 0, SEEK_END);
	length = ftell(ptr);
	rewind(ptr);

	char *File = malloc(sizeof(char *)*length);
	fread(File, sizeof(char), length, ptr);

	char ** sorted = malloc(sizeof(char*)*length);

	char * token1 = malloc(sizeof(char)*length);

	token1 = strtok(File, " \n\r");

	int i = 0;

	while( token1 != NULL )
	{
		sorted[i] = malloc(sizeof(char)*length);
		strcpy(sorted[i], token1);



		token1 = strtok(NULL, " \n\r");

		i++;
	}
	int j = 0;
	int t = 0;
	int w = 0;
	char * key = NULL;
	for(j = 0; j<i; j++)
	{
    	if(t == 0)
    	{	
    		key = sorted[j];
    		w = 0;
    	}
    	else if(t == 1)
    	{
    		hashNode * UserNodeInsert = NULL;
	    	UserNodeInsert = malloc(sizeof(hashNode));
	    	DataObject * UserInsert = NULL;
	    	UserInsert = malloc(sizeof(DataObject));
    		UserNodeInsert->key = malloc(sizeof(char)*strlen(key)+1);
    		UserInsert->systemDescriptor = malloc(sizeof(char)*strlen(key)+1);
    		UserInsert->password = malloc(sizeof(char)*strlen(sorted[j])+1);
    		
    		strcpy(UserInsert->systemDescriptor, key);
    		strcpy(UserNodeInsert->key, key);

		    strcpy(UserInsert->password, sorted[j]);

		    UserNodeInsert->data = (void*)UserInsert;

		    collisionCounter = insertData(htable, key, UserNodeInsert->data, collisionCounter);

    		t = 0;
    		w = 1;
    	}
    	if(t == 0 && w == 0)
    	{
    		t = 1;
    	}
	}
	return htable;
}
/**
Prints the data in the table to the given file
*/
void fprintTable(HTable * htable, FILE * file)
{
	clear();
	if(htable != NULL)
	{
		int index = 0;
		while(index < htable->tableSize)
		{
			if(htable->table[index] == NULL)
			{
				index++;
			}
			if(htable->table[index] != NULL)
			{
				hashNode * UserNodeOutput = NULL;
		    	DataObject * UserOutput = NULL;
		    	UserNodeOutput = malloc(sizeof(hashNode));
		    	UserOutput = malloc(sizeof(DataObject));
		    	UserOutput = htable->table[index]->data;
		    	UserNodeOutput->data = (void*)UserOutput;

		    	fprintf(file, "%s ", UserOutput->systemDescriptor);

		    	fprintf(file, "%s\n", UserOutput->password);

	    		index++;
			}
		}
		refresh();
	}
}
/**
Searches for the data inside the table and returns the index of the data
*/
void* lookupData(HTable* htable, char * key )
{
    if(htable != NULL)
    {
        int index = htable->hashFunction( htable->tableSize, key );

        if(htable->table[index] == NULL)
        {
            printMessage1("DATA NOT FOUND");
        }
        hashNode * temp = htable->table[index];
        if(temp != NULL)
        {
	        if(temp->next != NULL && (strcmp(temp->key, key) == 0))
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
    }
    else if(htable == NULL)
    {   
    	printMessage1("No Table");
    }
    return NULL;
}
/**
Prints to window and moves 2 down in the y direction
*/
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
/**
Prints to window and moves 1 down in the y direction
*/
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
/**
Moves 2 down in the y direction
*/
void moveTwoY()
{
	int x_coordinate, y_coordinate;
	getyx(stdscr, y_coordinate, x_coordinate);
	move(y_coordinate+1, x_coordinate - x_coordinate);
}