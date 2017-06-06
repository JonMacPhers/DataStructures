#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include "../include/QueueAPI.h"

int main(/*int argc, char	*argv[]*/)
{
	// Parse Text Data
	FILE* fp;
	//fp = fopen(argv[1], "r"); ***********DON'T FORGET TO FIX THIS*************
	fp = fopen("simulationTest.txt", "r");

	if(fp == NULL)
	{
		printf("File could not be read\n");
	}
	if(fp!=NULL)
	{
		int length = 0;
		fseek(fp, 0, SEEK_END);
		length = ftell(fp);
		rewind(fp);

		char *sample = malloc(sizeof(char *)*length);
		fread(sample, sizeof(char), length, fp);

		Queue *storage = NULL;
		storage = initializeQueue(&printC, &deleteMe, &printI);


		//Queue *parcedStorage = NULL;
		storage = parseFile(storage, sample, length);
		//char front = *(char*)Front(storage);
		printFrontToBack(storage);
		//Simulation(sample, length);
	}
	fclose(fp);
	return(0);
}