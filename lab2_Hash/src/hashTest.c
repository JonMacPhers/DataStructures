#include "../include/HashTableAPI.h"

int main(/*int argc, char	*argv[]*/)
{
	int tableSize = 50;
	int index = 0;
	//List* collisionList;
	//collisionList = initializeList(&printData, &deleteData, &compare);
	HTable* table;
	//HTable* collisions = createTable(100, &hashFunction, &deleteData, &printData);
	table = createTable(tableSize, &hashFunction, &deleteData, &printData);
	printf("\n\nTable of Size %d Created\n", table->tableSize);

	void * Me; 
	int iteration = 0;
	int key = 0;
	float socks = 0;

	//printf("\n*** Collision List ***\n");

	//Student student = {"Jon", "Mac", "Eng"};
	while(iteration<tableSize-20)
	{
		socks = ((((1+key)*2)+10)/2);
		Me = &socks;
		insertData(table, key, &Me);
		index = hashFunction(tableSize, key);
		printf("\n\nLocker #%d: %f sock(s)\n\n\n", table->table[index]->key, *(float*)table->table[index]->data);

		key++;
		iteration++;
	}
	//printForward(collisionList);

	index = hashFunction(tableSize, key);
	printf("\n\nLocker #%d: %d sock(s)\n\n\n", table->table[index]->key, *(int*)table->table[index]->data);


	return(0);
}