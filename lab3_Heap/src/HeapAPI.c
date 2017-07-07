#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "HeapAPI.h"
#include <string.h>



/*************Heap API*************/
/**This is used for all the functionality for the heap*/

/**
Helper function to print the data from a node
*/
void printData( void *toBePrinted )
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
void deleteData( void *data )
{
	DataObject * temp = data;
	free(temp->name);
	free(temp->number);
	free(temp);
	temp = NULL;
}
/**
Helper function to compare the data of a node
*/
int compareData(const void *first, const void *second)
{
	return 0;
}

/**
Creates a new Node
*/
heapNode * initializeNode( int key, void * data)
{
	if(data != NULL)
	{
		heapNode * newNode = NULL;
		newNode = (heapNode *)malloc(sizeof(heapNode));
		newNode->left = NULL;
		newNode->right = NULL;
		newNode->parent = NULL;
		newNode->data = NULL;
		newNode->left = (heapNode *)malloc(sizeof(heapNode));
		newNode->right = (heapNode *)malloc(sizeof(heapNode));
		newNode->parent = (heapNode *)malloc(sizeof(heapNode));
		newNode->data = malloc(sizeof(void*));
		if(newNode->data != NULL)
		{
			newNode->data = data;
			return newNode;
		}
		else
		{
			free(newNode->left);
			free(newNode->right);
			free(newNode->parent);
			free(newNode->data);
			free(newNode);
			return NULL;
		}
	}
	return NULL;
}
/**
Creates the Heap
*/
Heap * createHeap( char * htype,
        void (*destroyDataFP)(void *data),
        void (*printNodeFP)(void *toBePrinted),
        int (*compareFP)(const void *first, const void *second))
{
	//New Heap
	Heap * newHeap = NULL;

	/* Allocate the Heap itself. */
	if( ( newHeap = malloc(sizeof(Heap)) ) == NULL )
	{
		return NULL;
	}
	/* Allocate pointer to the first heap node */
	if( (newHeap->heap = (heapNode *)malloc(sizeof(heapNode))) == NULL )
	{
		return NULL;
	}
	/* Allocate pointer to the lastPosition of the tree */
	if( (newHeap->lastPosition = (heapNode *)malloc(sizeof(heapNode))) == NULL )
	{
		return NULL;
	}
	if(strcmp(htype,"max") == 0)
	{
		newHeap->type = 1;
	}
	else if(strcmp(htype,"min") == 0)
	{
		newHeap->type = -1;
	}
	else if(strcmp(htype,"min") != 0 && strcmp(htype,"max") == 0)
	{
		printf("\nInvalid Type\n\n");
		return NULL;
	}
	newHeap->compareData = compareFP;
	newHeap->deleteData = destroyDataFP;
	newHeap->printData = printNodeFP;
	return newHeap;
}
/**
Destroys the Heap
*/
void destroyHeap( Heap * h )
{
	//heapNode * nodePtr;
	//Heap * heapPtr;
	//heapNode = h->heap;	//sets nodePtr to first node in heap??
}
/**
Inserts Data to the Heap
*/
void insertHeapNode( Heap * h, int key, void * data )
{
	if( h != NULL)
	{
		heapNode * newNode;
		heapNode * temp;
		temp = h->heap;
		newNode = initializeNode( key, data );
		if(temp->data == NULL)
		{// ROOT OF TREE
			h->heap = newNode;
			h->lastPosition = newNode;
		}
		else if(temp->data != NULL)
		{
			if(h->type > 0)
			{//Max Heap
				lessGreater(h, newNode, data, temp);
			/*	if(*(int*)data < *(int*)(h->heap->data))
				{// Level 1, left < right
					printf("\nMAX less than\n\n");
					if(temp->left->data == NULL)
					{
						newNode->parent = h->heap;
						temp->left = newNode;
						h->lastPosition = newNode;
					}
					else if(temp->left->data != NULL)
					{
						temp = h->heap->left;
						if(*(int*)data < *(int*)(temp->data))
						{// Level 2, left > right
							if(temp->right == NULL)
							{
								printf("\nLeft: Level 2 less than: RIGHT\n\n");
								newNode->parent = temp;
								temp->right = newNode;
							}
							else if(temp->right != NULL)
							{	
								lessGreater(h, newNode, data);
							}
						}
						else if(*(int*)data > *(int*)(h->heap->data))
						{
							printf("\nLeft: Level 2 greater than: LEFT\n\n");
							newNode->parent = temp;
							temp->left = newNode;
							h->lastPosition = newNode;
						}
					}
				}
				else if(*(int*)data > *(int*)(h->heap->data))
				{
					printf("\nMAX greater than\n\n");
					if(temp->right->data == NULL)
					{// Level 1, left < right
						newNode->parent = h->heap;
						temp->right = newNode;
					}
					else if(temp->left->data != NULL)
					{
						temp = temp->right;
						if(*(int*)data < *(int*)(temp->data))
						{// Level 2, left > right
							printf("\nRight: Level 2 less than: RIGHT\n\n");
							newNode->parent = temp;
							temp->right = newNode;
						}
						else if(*(int*)data > *(int*)(h->heap->data))
						{
							printf("\nRight: Level 2 greater than: LEFT\n\n");
							newNode->parent = temp;
							temp->left = newNode;
							h->lastPosition = newNode;
						}
					}
				}*/
			}
			else if(h->type < 0)
			{//Min Heap
				if(data < h->lastPosition->data)
				{
					printf("\nMIN less than\n\n");
				}
				else if(data > h->lastPosition->data)
				{
					printf("\nMIN greater than\n\n");
				}
			}
		}
		return;
	}
	else
		printf("\nNo Heap Found\n\n");
		return;
}

void searchTree(Heap * h, int key)
{
	/* Navigate to the left most node, (print data), navigate to parent, *check right* (if right, print data), navigate to parent, etc  */
}

Heap * heapifyData( Heap * h )
{
	return h;
}
void lessGreater(Heap * h, heapNode * newNode, void * data, heapNode * oldTemp)
{
	heapNode * temp;
	if(*(int*)data > *(int*)(oldTemp->data))
	{// left < right
		temp = oldTemp->right;
		if(temp->data == NULL)
		{
			printf("\nLevel # greater than: RIGHT\n\n");
			newNode->parent = temp;
			temp->right = newNode;
		}
		else if(temp->data != NULL)
		{
			greaterLess(h, newNode, data, temp);
		}
	}
	else if(*(int*)data < *(int*)(oldTemp->data))
	{// left < right
		temp = oldTemp->left;
		if(temp->data == NULL)
		{
			printf("\nLevel # less than: LEFT\n\n");
			newNode->parent = temp;
			temp->left = newNode;
			h->lastPosition = newNode;
		}
		else if(temp->data != NULL)
		{
			greaterLess(h, newNode, data, temp);
		}
	}
}

void greaterLess(Heap * h, heapNode * newNode, void * data, heapNode * oldTemp)
{
	heapNode * temp;
	if(*(int*)data < *(int*)(oldTemp->data))
	{// left > right
		temp = oldTemp->right;
		if(temp->data == NULL)
		{
			printf("\nLevel # less than: RIGHT\n\n");
			newNode->parent = temp;
			temp->right = newNode;
		}
		else if(temp->data != NULL)
		{
			lessGreater(h, newNode, data, temp);
		}
	}
	else if(*(int*)data > *(int*)(oldTemp->data))
	{// left > right
		temp = oldTemp->left;
		if(temp->data == NULL)
		{
			printf("\nLevel # greater than: LEFT\n\n");
			newNode->parent = temp;
			temp->left = newNode;
			h->lastPosition = newNode;
		}
		else if(temp->data != NULL)
		{
			lessGreater(h, newNode, data, temp);
		}
	}
}










