#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "HeapAPI.h"
#define SIZE 50

/**
This is the main function for the CIS*2520 Second assignment. Inside we are to create a Hash Table for storing passwords tied to keys inside the hash table.
- Jonathan Macpherson
*/

int main() {

	printf("\n\n ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
	printf("<======================================================>\n");
	printf("<==================Check Out My Tree===================>\n");
	printf("<======================================================>\n");
	printf(" ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");

	Heap * heap;
	heap = createHeap( "max", &deleteData, &printData, &compareData );

	int input = 5;
	int input2 = 1;
	int input3 = 2;
	int input4 = 6;
	int input5 = 8;

	insertHeapNode( heap, 0, &input);

	printf("\n Root Data = %d\n\n", *(int*)(heap->heap->data));

	insertHeapNode( heap, 2, &input3);
	printf("\n\nHMMMMMM\n\n");
	printf("\n%d\n\n", *(int*)(heap->heap->left->data));

	insertHeapNode( heap, 1, &input2);
	printf("\n%d\n\n", *(int*)(heap->heap->left->right->data));

	insertHeapNode( heap, 3, &input4);
	printf("\n%d\n\n", *(int*)(heap->heap->right->data));

	insertHeapNode( heap, 4, &input5);
	printf("\n%d\n\n", *(int*)(heap->heap->right->left->data));
	
	return(0);
}
