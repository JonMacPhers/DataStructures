#include "../include/QueueAPI.h"
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>

/*
 - The ADT Queue is a linear sequence of an arbitrary number of items, together
with access procedures.
 - The access procedures permit addition only at the back of the queue and
deletion of items only at the front of the queue.
 - The queue is a queue structure sometimeSecs called a first-in-first-out (or FIFO) queue
 - A queue is either empty, or it consists of a sequence of items. Manipulations or
accesses to these items are only permitted at the two ends of the queue.
*/

// -------      -------      -------
// | Back |---> |      |---> | Front |
// -------      -------      -------
//previous = left
//next = right
void printC(void *printme)
{
	printf("%c\n", *(char*)printme);
	return ;
}

void printI(void *printme)
{
	printf("%d\n", *(int*)printme);
	return ;
}

void deleteMe(void *deleteme)
{
	free(deleteme);
	return;
}

Queue *initializeQueue(void (*printCharFunction)(void *charPrinted),void (*deleteFunction)(void *toBeDeleted),void (*printIntFunction)(void *intPrinted))
{
	//New Queue pointer
	Queue* queue;
	queue = malloc(sizeof(struct queueCommander));
	
	//Check for creation OK!
	if (queue == NULL)
	{
		return NULL;
	}
		
	//malloc the Front pointer
	queue->Front = (Car *)malloc(sizeof(Car));
	queue->Back = (Car *)malloc(sizeof(Car));
	queue->Front = NULL;
	queue->Back = NULL;
	
	//Set the function pointers to the functions passed in
	queue->printC = printCharFunction;
	queue->deleteData = deleteFunction;
	queue->printI = printIntFunction;
	return queue;
}
//Creates a new Car and returns pointer to it. 
Car *initializeCar(void *direction, void *path, void *clock)
{
	if ((direction != NULL)&&(path != NULL)&&(clock != NULL))
	{
		Car* car = NULL;
		car = (Car *)malloc(sizeof(Car));
		car->direction = NULL;
		car->direction = malloc(sizeof(char));
		car->path = NULL;
		car->path = malloc(sizeof(char));
		car->clock = NULL;
		car->clock = malloc(sizeof(int));
		car->previous = NULL;
		car->previous = (Car *)malloc(sizeof(Car));
		car->next = NULL;
		car->next = (Car *)malloc(sizeof(Car));
	
		if ((car->direction!=NULL)&&(car->path!=NULL)&&(car->clock!=NULL))
		{
			printf("not NULL\n");
			car->direction = &direction;
			car->path = &path;
			car->clock = &clock;
			car->previous = NULL;
			car->next = NULL;
			return car;
		}
		else 
		{
			printf("Error\n");
			free(car->previous);
			free(car->next);
			free(car->direction);
			free(car->path);
			free(car->clock);
			free(car);
			return NULL;
		}
	}
	return NULL;
}
Queue *enqueue(Queue *queue, void *toBeAdded1, void *toBeAdded2, void *toBeAdded3)
{//check if theres a queue
	if (queue == NULL)
	{
		printf("NULL Queue");
		return queue;
	}
	if (queue->Front == NULL)
	{// if no elements create element
		printf("First Car\n");
		Car* newCar = NULL;
		newCar = initializeCar(&toBeAdded1, &toBeAdded2, &toBeAdded3);
		queue->Front = newCar;
		queue->Back = newCar;
		queue->Front->next = NULL;
		queue->Back->previous = NULL;
		return queue;
	}//if element at Front, traverse to back and insert backk
	else if (queue->Front != NULL)
	{
		Car* frontPtr;
		frontPtr = queue->Front;
		while(frontPtr->previous != NULL)
		{	
			frontPtr = frontPtr->previous;
		}
		printf("New Car\n");
		Car* newCar = NULL;
		newCar = initializeCar(&toBeAdded1, &toBeAdded2, &toBeAdded3);
		
		frontPtr->previous = newCar;
		newCar->next = queue->Back;	//pointing at Back most memory spot
		newCar->previous = NULL;
		queue->Back = newCar;		//Back of queue to new Car
		return queue;
	}
	return queue;
}
/** Deletes the entire linked queue Front to Back, starting with the Cars, followed by the queue itself.
*@pre 'queue' type must exist and be used in order to keep track of the linked queue.
*@param queue pointer to the queue-type dummy Car
**/
void deletequeue(Queue *queue)
{//check if theres a queue
	if (queue == NULL)
	{
		return;
	}
		
	/* queue exist but no elements */
	if ((queue != NULL)&&(queue->Front == NULL))
	{
		free(queue->Back);
		queue->Back=NULL;
		free(queue->Front);
		queue->Front=NULL;
		free(queue);
		queue=NULL;
		return;
	}

	/* queue exists with elements */
	if((queue!=NULL)&&(queue->Front!=NULL))
	{	
		Car* ptr1;
		ptr1 = queue->Front;
		while(ptr1->previous!=NULL){
			Car* ptr2;
			ptr2 = ptr1->previous;
			ptr1 = ptr2;
		}	
	}
	free(queue);
	printf("Deletion Successful\n");
}
/**Function to return the direction at the front of the queue.
 *@pre The queue exists and has memory allocated to it
 *@param queue pointer to the dummy Front of the queue containing the Front of the queue
 *@return pointer to the direction located at the Front of the queue
 **/
void *Front(Queue *queue)
{
	if (queue == NULL)
	{
		return NULL;
	}
		
	else if ((queue!=NULL)&&(queue->Front!=NULL))
	{
		return queue->Front->direction;
	}
		
	return NULL;
}

/**Function to return the direction at the back of the queue.
 *@pre The queue exists and has memory allocated to it
 *@param queue pointer to the dummy Front of the queue containing the Back of the queue
 *@return pointer to the direction located at the Back of the queue
 **/
void *deQueue(Queue *queue)
{
	if (queue == NULL)
	{
		return NULL;
	}
		
	else if ((queue!=NULL)&&(queue->Back!=NULL))
	{
		return queue->Back->direction;
		free(queue->Back);
	}
		
	return NULL;
}
void printFrontToBack(Queue *queue)
{//check if theres a queue
	if (queue == NULL)
	{
		return;
	}
	if ((queue != NULL) && (queue->Front != NULL))
	{
		Car* cPtr = NULL;
		cPtr = queue->Front;
		while(cPtr->previous != NULL)
		{
			queue->printC(&cPtr->direction);
			queue->printC(&cPtr->path);
			queue->printI(&cPtr->clock);
			cPtr = cPtr->previous;
		}	
	}
}
/*
int *searchDataForCar(Queue *list, void *toSearch) {
	Car *temp = list->Front;
	int which[100];
	//which = malloc(sizeof(char)*200);
	int count=0;
	int index=0;
	while(temp->next!=NULL) {
		if(temp->direction==toSearch||temp->path==toSearch||temp->clock==toSearch) {
			which[index]=count;
			index++;
		}
		count++;
		temp=temp->next;
	}
	return which;
}
*/ 
void Simulation(char *simData, int length)
{	
	//clock_t start_t, end_t, total_t;
	int i;
	//int timeSec;	
	for(i = 0; i<length; i++)
	{
		if(i == 0)
		{
			printf("We Gucci %d", i);
		}
		if( simData[i] == 'N' )
		{	
			i += 2;
			//Queue* drivingNorth;
			//drivingNorth = initializeQueue(&print, &deleteMe, &comparedirection);
			printf("North\n");
			if( simData[i] == 'F' )
			{	
				printf("Forward\n");
			}
			else if( simData[i] == 'L' )
			{
				printf("Left\n");
			}
			else if( simData[i] == 'R' )
			{
				printf("Right\n");
			}
			i += 2;;
			//int delayN = atoi(&simData[i]);
			printf("Time: %d seconds", atoi(&simData[i]));
		}
		else if( simData[i] == 'E' )
		{
			i += 2;
			//Queue* drivingEast;
			//drivingEast = initializeQueue(&print, &deleteMe, &comparedirection);
			printf("East\n");
			if( simData[i] == 'F' )
			{
				printf("Forward\n");
			}
			else if( simData[i] == 'L' )
			{
				printf("Left\n");
			}
			else if( simData[i] == 'R' )
			{
				printf("Right\n");				
			}
			i += 2;
			//int delayE = atoi(&simData[i]);
			printf("Time: %d seconds", atoi(&simData[i]));			
	/*			if(timeSec == delayE)
				{
					//Car* newCar;
					//newCar = (Car*)malloc(sizeof(Car));
					//char x, y;
					i -= 4;
					//x = simData[i];
					i += 2;
					i += 2;
					//newCar = enqueue(drivingEast, x, y, delayE);
				}
	*/	
		}
		else if( simData[i] == 'S' )
		{
			i += 2;
			//Queue* drivingSouth;
			//drivingSouth = initializeQueue(&print, &deleteMe, &comparedirection);
			printf("South\n");
			if( simData[i] == 'F' )
			{
				printf("Forward\n");
			}
			else if( simData[i] == 'L' )
			{
				printf("Left\n");
			}
			else if( simData[i] == 'R' )
			{
				printf("Right\n");				
			}
			i += 2;
			//int delayS = atoi(&simData[i]);
			printf("Time: %d seconds", atoi(&simData[i]));			
	/*			if(timeSec == delayS)
				{
					//Car* newCar;
					//newCar = (Car*)malloc(sizeof(Car));
					//char x, y;
					i -= 4;
					//x = simData[i];
					i += 2;
					i += 2;
					//newCar = enqueue(drivingSouth, x, y, delayS);
				}
	*/
		}
		else if( simData[i] == 'W' )
		{
			i += 2;
			//Queue* drivingWest;
			//drivingWest = initializeQueue(&print, &deleteMe, &comparedirection);
			printf("West\n");
			if( simData[i] == 'F' )
			{
				printf("Forward\n");
			}
			else if( simData[i] == 'L' )
			{
				printf("Left\n");
			}
			else if( simData[i] == 'R' )
			{
				printf("Right\n");				
			}
			i += 2;
			//int delayW = atoi(&simData[i]);
			printf("Time: %d seconds", atoi(&simData[i]));
		/*		if(timeSec == delayW)
				{
					//Car* newCar;
					//newCar = (Car*)malloc(sizeof(Car));
					//char x, y;
					i -= 4;
					//x = simData[i];
					i += 2;
					i += 2;

					//newCar = enqueue(drivingWest, x, y, delayW);
				}
		*/
		}
	}
}
//Queue *memory, 
Queue *parseFile(Queue *queue, char *simData, int length)
{	
	//clock_t start_t, end_t, total_t;
	int i;
	char direct;
	char path;
	int delay;
	if((queue != NULL) && (simData != NULL))
	{
		if(queue == NULL)
		{
			printf("NULL Queue");
		}
		for(i = 0; i<length; i++)
		{
			direct = simData[i];
			//printf("%c ", simData[i]);

			i += 2;

			path = simData[i];
			//printf("%c ", simData[i]);
			i += 2;

			if( simData[i+1] != '\n' && simData[i+1] != '\r' )
			{
				int tmp;
				tmp = i;
				while( (simData[i+1] != '\n') && (simData[i+1] != '\r') )
				{	
					i++;
					if(simData[i] < simData[length])
					{	
						break; break;
					}
				}
				char *buffer = malloc(sizeof(char *)*(i-tmp));
				strncpy(buffer, simData + tmp, i-tmp+1);
				delay = atoi(buffer);
				//printf("%d\n", atoi(buffer));
				i+=2;
			}
			else if( simData[i+1] == '\n' || simData[i+1] == '\r' )
			{
				delay = atoi(&simData[i]);
				//printf("%d\n", atoi(&simData[i]));
				i+=2;
			}
			queue = enqueue(queue, &direct, &path, &delay);
		}
	}
	return queue;
}