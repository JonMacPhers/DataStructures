#include "LinkedListAPI.h"

List *initializeList(void (*printFunction)(void *toBePrinted),void (*deleteFunction)(void *toBeDeleted),int (*compareFunction)(const void *first,const void *second))
{
	//New List pointer
	List* top;
	top = malloc(sizeof(struct listHead));
	
	//Check for creation OK!
	if (top == NULL)
		return NULL;
		
	//malloc the head pointer
	top->head = malloc(sizeof(Node*));
	top->tail = malloc(sizeof(Node*));
	top->head = NULL;
	top->tail = NULL;
	
	//Set the function pointers to the functions passed in
	top->printData = printFunction;
	top->deleteData = deleteFunction;
	top->compare = compareFunction;
	return top;
}
Node *initializeNode(void *data)
{
	if (data != NULL)
	{
		Node* node = malloc(sizeof(Node));
		node->data = malloc(sizeof(void*));
		node->next = malloc(sizeof(Node*));
		node->previous = malloc(sizeof(Node*));
	
		if ((node->data!=NULL)&&(node->next!=NULL)&&(node->previous!=NULL))
		{
			node->data = data;
			node->next = NULL;
			node->previous = NULL;
			return node;
		}
		else 
		{
			free(node->next);
			free(node->previous);
			free(node->data);
			free(node);
			return NULL;
		}
	}
	return NULL;
}
void insertFront(List *list, void *toBeAdded)
{
	if (list == NULL)
	{
		return;
	}
	if (list->head == NULL)
	{
		Node* newNode = NULL;
		newNode = initializeNode(toBeAdded);
		list->head = newNode;
		list->tail = newNode;
		return;
	}
	if (list->head!=NULL)
	{
		Node* newNode = NULL;
		newNode = initializeNode(toBeAdded);
		Node* tmpptr = list->head; //pointing at the old first node
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
		Node* tempPtr = list->head;
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
}
void printBackwards(List *list)
{
	if (list == NULL)
	{
		return;
	}
	if ((list != NULL) && (list->tail != NULL))
	{
		Node* tempPtr = list->tail;
		
		
		do
		{
			list->printData(tempPtr->data);
			printf(", ");
			tempPtr = tempPtr->previous;
		}
		while(tempPtr->previous!= NULL);
		
		list->printData(tempPtr->data);
		tempPtr = tempPtr->previous;
	}
	printf("\n");
}
void *getFromBack(List *list)
{
	if (list == NULL)
		return NULL;
		
	if ((list!=NULL)&&(list->tail!=NULL))
		return list->tail->data;
		
	return NULL;
}
void *getFromFront(List *list)
{
	if (list == NULL)
		return NULL;
		
	if ((list!=NULL)&&(list->tail!=NULL))
		return list->head->data;
		
	return NULL;
}
void deleteList(List *list)
{
	/* DNE */
	if (list == NULL)
	{
		return;
	}	
	/* List exist but no elements */
	if ((list != NULL)&&(list->head == NULL))
	{
		free(list->tail);
		free(list->head);
		free(list);
		list = NULL;
		return;
	}
	if ((list != NULL)&&(list->head != NULL))
	{
		Node* currentNode = list->head;
		Node* nextNode;
		
		while(currentNode->next != NULL)
		{
			nextNode = currentNode->next;
			currentNode->data = NULL;
			free(currentNode);
			currentNode = nextNode;
		}
		currentNode->data = NULL;
		free(currentNode);
		free(list);	
		return;	
	}
	return;
}
void insertBack(List *list, void *toBeAdded)
{
	if (list == NULL)
	{
		return;
	}
	if (list->tail == NULL)
	{
		Node* newNode = NULL;
		newNode = initializeNode(toBeAdded);
		list->head = newNode;
		list->tail = newNode;
		return;
	}
	if (list->tail!=NULL)
	{
		Node* newNode = NULL;
		newNode = initializeNode(toBeAdded);
		Node* tmpptr = list->tail; //pointing at the old first node
		list->tail = newNode;		//head of list to new node
		newNode->previous = tmpptr;		//newnodes next ptr is the old head
		tmpptr->next = newNode;
		return;
	}
	else
	{
		return;
	}
	return;
}
int deleteDataFromList(List *list, void *toBeDeleted)
{
	if (list == NULL)
	{
		return EXIT_FAILURE;
	}
	if ((list != NULL)&&(list->head == NULL))
	{
		return EXIT_FAILURE;
	}
	if ((list != NULL)&&(list->head != NULL))
	{
		Node* tmpPtr1 = NULL;
		Node* tmpPtr2 = NULL;		
		Node* tmpPtr = NULL;
		tmpPtr = list->head;
		
		do{
			if (toBeDeleted == tmpPtr->data)
			{
				/* Element is the first element */
				if (tmpPtr->previous == NULL)
				{
					tmpPtr1 = tmpPtr->next;
					list->head = tmpPtr->next;
					list->deleteData(toBeDeleted);
					tmpPtr1->previous = NULL;
					free(tmpPtr);
					return EXIT_SUCCESS;
				}
				/* Element is in the middle */
				if ((tmpPtr->next != NULL)&&(tmpPtr->previous != NULL))
				{
					tmpPtr1 = tmpPtr->previous;
					tmpPtr2 = tmpPtr->next;
					
					tmpPtr1->next = tmpPtr2;
					tmpPtr2->previous = tmpPtr1;
					
					list->deleteData(toBeDeleted);
					free(tmpPtr);
					return EXIT_SUCCESS;
				}
			}
			tmpPtr = tmpPtr->next;
		}while(tmpPtr->next != NULL);
		
		if (toBeDeleted == tmpPtr->data)
		{
			/* Element is the last element */
			tmpPtr1 = tmpPtr->previous;
			list->tail = tmpPtr->previous;
			list->deleteData(toBeDeleted);
			tmpPtr1->next = NULL;
			free(tmpPtr);
			return EXIT_SUCCESS;
		}
	}
	return -1;
}
void insertSorted(List *list, void *toBeAdded)
{
	/* List DNE */
	if (list == NULL)
		return;
		
	/* List Exist, but no items, just add to the front */
	if ((list != NULL) && (list->head == NULL))
	{
		insertFront(list, toBeAdded);
		return;
	}
	if ((list != NULL) && (list->head != NULL))
	{
		Node* currNode;
		Node* nextNode;
	
		currNode = list->head;
		nextNode = list->head->next;
		
		while(currNode->next != NULL)
		{	
			if (list->compare(toBeAdded, currNode->data) >= 0)
			{
				Node* newNode = NULL;
				newNode = initializeNode(toBeAdded);
				
				currNode->next = newNode;
				newNode->previous = currNode;
				newNode->next = nextNode;
				nextNode->previous = newNode;
				return;
			}
			currNode = nextNode;
			nextNode = nextNode->next;
		}
		insertBack(list, toBeAdded);
		return;
	}
	return;	
}


