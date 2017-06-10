#include "../include/HashTableAPI.h"

int main(/*int argc, char	*argv[]*/)
{
	int tableSize = 5;
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
	int collisionCounter = 0;
	float socks = 0;

	while(iteration<tableSize)
	{
		socks = ((((1+key)*16.789)+10)/2);
		Me = &socks;
		printf("\nKEY %d\n\n", key);
		collisionCounter = insertData(table, key, Me, collisionCounter);
		index = table->hashFunction(tableSize, key);
		printf("\n\nLocker #%d: %.0f socks\n\n\n", key, *(float*)table->table[index]->data);

		key++;
		iteration++;
	}
	printf("\n\n\n\n\n");
	int newkey = 0;

	while(newkey<tableSize)
	{	
		int index = 0;	
		index = table->hashFunction(tableSize, newkey);
		printf("\n\nLocker #%d: %.0f socks\n\n\n", index, *(float*)table->table[index]->data);
		newkey++;
	}
	// Last Value Collides with first index
	/*key = 7;
	index = hashFunction(tableSize, key);
	removeData(table, key);
	printf("\n\nLocker #%d: %.0f socks\n\n\n", table->table[index]->key, *(float*)table->table[index]->data);
	*/
	return(0);
}