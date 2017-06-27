#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "vaultAPI.h"
#define SIZE 50

/**
This is the main function for the CIS*2520 Second assignment. Inside we are to create a Hash Table for storing passwords tied to keys inside the hash table.
- Jonathan Macpherson
*/

int main() {

	char * adminUsername = "use";
	char * adminPassword = "pas";
	char inputUsername[20];
	char inputPassword[20];

	initscr();
	cbreak ();
	noecho ();

	printMessage2("Admin Username Required: ");
	getstr(inputUsername);
	printMessage2("Admin Password Required: ");
	getstr(inputPassword);
	echo();
	if((strcmp(adminUsername, inputUsername) == 0) && (strcmp(adminPassword, inputPassword) == 0))
	{
		int collisionCounter = 0;
		HTable * UserDB;
		UserDB = createTable(SIZE, &hashFunction, &deleteData, &printData);

		// Parse Text Data
		FILE* fp;
		fp = fopen("vault.txt", "r");

		if(fp == NULL)
		{
			printf("File could not be read\n");
		}
		if(fp != NULL)
		{
			parseFile(UserDB, fp, collisionCounter);
		}

	    int Loop = 1;

	    //Loops until Quit is entered
	    while(Loop == 1)
	    {
	    	//This loop is used as the Command loop, it checks all the possibilities of entries into the main menu for validation
	    	clear();
	    	char * message;
	    	char input[100];
	    	int input1;
	    	wmove(stdscr,0,0);
	    	printMessage1(" //*****************************************************************************\\");
	    	printMessage1("||==============================> Password Vault <==============================||");
	    	printMessage1(" \\*****************************************************************************//");
		    message = "Select one of the following, by entering the corresponding value in it's brackets:";
		    printMessage1(message);
		    moveTwoY();
		    message = "-> (1) Store Password";
		    printMessage1(message);
		    message = "-> (2) Retrieve Password";
		    printMessage1(message);
		    message = "-> (3) Change Password";
		    printMessage1(message);
		    message = "-> (4) Delete Password";
		    printMessage1(message);
		    message = "-> (Quit) Quit";
		    printMessage1(message);
		    moveTwoY();
		    getstr(input);
		    moveTwoY();
		    input1 = (int)strtol(input, NULL, 10);
		    if(input1 == 1)
		    {
		    	//Control statement for Inserting new node into the table
		    	char buffer1[100];
		    	hashNode * UserNodeInsert = NULL;
		    	UserNodeInsert = malloc(sizeof(hashNode));
		    	DataObject * UserInsert = NULL;
		    	UserInsert = malloc(sizeof(DataObject));
		    	printMessage1("Please create/enter a key for your account :)");
		    	moveTwoY();
		    	getstr(buffer1);
		    	moveTwoY();
		    	UserNodeInsert->key = malloc(sizeof(char)*strlen(buffer1)+1);
		    	strcpy(UserNodeInsert->key, buffer1);
		    	UserInsert->systemDescriptor = malloc(sizeof(char)*strlen(buffer1)+1);
		    	strcpy(UserInsert->systemDescriptor, buffer1);
		    	printMessage1("Please enter the password you would like to store:");
		    	moveTwoY();
		    	getstr(buffer1);
		    	moveTwoY();
		    	UserInsert->password = malloc(sizeof(char)*strlen(buffer1)+1); 
		    	strcpy(UserInsert->password, buffer1);
		    	
		    	UserNodeInsert->data = (void*)UserInsert;
		    	
		    	collisionCounter = insertData(UserDB, UserInsert->systemDescriptor, UserNodeInsert->data, collisionCounter);

		    	refresh();
		    }
		    else if(input1 == 2)
		    {
		    	//Control statement for searching for a node
		    	char buffer2[100];
		    	printMessage1("Please enter your key:");
		    	moveTwoY();
		    	getstr(buffer2);
		    	moveTwoY();
		    	if(UserDB->table[hashFunction(UserDB->tableSize, buffer2)] == NULL)
		    	{
		    		printw("Key: %s doesn't match any passwords sorry :'(", buffer2);
		    		moveTwoY();
		    		moveTwoY();
		    	}
		    	else if(UserDB->table[hashFunction(UserDB->tableSize, buffer2)] != NULL)
			    {	
			    	hashNode * UserNodeOutput = NULL;
			    	DataObject * UserOutput = NULL;
			    	DataObject * UserCheck = NULL;
			    	UserNodeOutput = malloc(sizeof(hashNode));
			    	UserOutput = malloc(sizeof(DataObject));
			    	UserCheck = malloc(sizeof(DataObject));
			    	UserCheck = UserDB->table[UserDB->hashFunction(SIZE, buffer2)]->data;
			    	UserOutput = lookupData(UserDB, buffer2);
			    	UserNodeOutput->data = (void*)UserOutput;

			    	if(UserDB->table[UserDB->hashFunction(SIZE, UserCheck->systemDescriptor)] != NULL)
				    {
				    	if((UserOutput->password != NULL) && (UserOutput->systemDescriptor != NULL))
				    	{
				    		printw("Saved Password-> %s", UserOutput->password);
				    		moveTwoY();
				    		moveTwoY();
				    	}
				    }
				}
		    	else
		    	{
		    		printMessage2("Password not found :$");
		    	}
		    	refresh();
		    }
		    else if (input1 == 3)
		    {
		    	//Control statement for editing a node
		    	char buffer3[100];
		    	hashNode * UserNodeInsert2 = NULL;
		    	UserNodeInsert2 = malloc(sizeof(hashNode));
		    	DataObject * UserInsert2 = NULL;
		    	UserInsert2 = malloc(sizeof(DataObject));
		    	printMessage1("Please enter the key for your password:");
		    	moveTwoY();
		    	getstr(buffer3);
		    	moveTwoY();
		    	if(UserDB->table[hashFunction(SIZE, buffer3)] == NULL)
		    	{
		    		printw("Key: %s doesn't match any passwords sorry :'(", buffer3);
		    		moveTwoY();
		    		moveTwoY();
		    	}
		    	else if(UserDB->table[hashFunction(UserDB->tableSize, buffer3)] != NULL)
			    {	
			    	removeData(UserDB, buffer3);
			    	moveTwoY();
			    	if(UserDB->table[hashFunction(UserDB->tableSize, buffer3)] == NULL)
			    	{
			    		UserNodeInsert2->key = malloc(sizeof(char)*strlen(buffer3)+1);
				    	strcpy(UserNodeInsert2->key, buffer3);
				    	UserInsert2->systemDescriptor = malloc(sizeof(char)*strlen(buffer3)+1);
				    	strcpy(UserInsert2->systemDescriptor, buffer3);
				    	printMessage1("Please enter your new password:");
				    	moveTwoY();
				    	getstr(buffer3);
				    	moveTwoY();
				    	UserInsert2->password = malloc(sizeof(char)*strlen(buffer3)+1); 
				    	strcpy(UserInsert2->password, buffer3);
				    	UserNodeInsert2->data = (void*)UserInsert2;
				    	collisionCounter = insertData(UserDB, UserInsert2->systemDescriptor, UserNodeInsert2->data, collisionCounter);
				    	moveTwoY();
				    	refresh();
			    	}
			    }
		    }

		    else if (input1 == 4)
		    {
		    	//Control statement for deleting a node
		    	char buffer4[100];
		    	printMessage1("Please enter the key of the password you would like to delete :'(");
		    	moveTwoY();
		    	getstr(buffer4);
			    if(UserDB->table[UserDB->hashFunction(SIZE, buffer4)] != NULL)
			    {
			    	removeData(UserDB, buffer4);
			    	printMessage2("Deleted");
		    	}
		    	else if(UserDB->table[UserDB->hashFunction(SIZE, buffer4)] == NULL)
		    	{
		    		moveTwoY();
		    		printw("key: %s, doesn't match any passwords.", buffer4);
		    		moveTwoY();
		    	}
		    	refresh();
		    }
		    else if (strcmp(input,"Quit") == 0)
		    {
		    	printMessage1(" //*****************************************************************************\\");
	    		printMessage1("||================================> Bye For Now <===============================||");
	    		printMessage1(" \\*****************************************************************************//");
		    	break;
		    }
		    else
		    {
		    	printMessage1("Invalid Input :'(");
		    	printMessage2("Please try again :')");
		    }
		    printMessage1(" //*****************************************************************************\\");
	    	printMessage1("||==========================> Press Any Key To Continue <=======================||");
	    	printMessage1(" \\*****************************************************************************//");
		    refresh();
		    noecho();
		    getch();
		    echo();
		}
	FILE * print;
	print = fopen("vault.txt", "w");
	fprintTable(UserDB, print);
	fclose(print);	
	}
	else if((strcmp(adminUsername, inputUsername) != 0) && (strcmp(adminPassword, inputPassword) != 0))
	{
		printMessage2("Invalid admin information");
	}
refresh();
endwin();
return(0);
}
