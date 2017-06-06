#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "../include/QueueAPI.h"

/*
int parseFile()
{	
	FILE* fp;
	fp = fopen("simulationTest.txt" , "r");

	if(fp == NULL)
	{
		//printf("File could not be read\n");
	}
	if(fp!=NULL)
	{	
		char simData[50];
		fgets(simData, 10, fp);
		if( simData[0] == 'N' )
		{
			printf("North\n");
		}
		else if( simData[0] == 'E' )
		{
			printf("East\n");
		}
		else if( simData[0] == 'S' )
		{
			printf("South\n");
		}
		else if( simData[0] == 'W' )
		{
			printf("West\n");				
		}
//		fread(array, sizeof(char), length, fp);
//		fread(array, sizeof(int), length, fp);
	}
	return(0);
}
*/


int main(){
	parseFile();
/*	FILE* fp; 
	fp = fopen("../simulationTest.txt", "r");
	int line = 0;
	char *input = malloc(sizeof(char)*500);

	if(fp==NULL)
	{
		printf("file cannot be read");
	}
	while( line!=10 )
	{
		fgets(input, 500, fp);
		printf("cat\n");
		line++;
		printf("Line:%d -> %s", line, input);
	}
	printf("\n\nThat's All Folks");

	fclose(fp); 
	*/
	return(0);
}