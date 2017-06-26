#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "vaultAPI.h"
#define SIZE 50

int main(/*int argc, char	*argv[]*/) {
/*
	// Parse Text Data
	FILE* fp;
	//fp = fopen(argv[1], "r"); ***********DON'T FORGET TO FIX THIS*************
	fp = fopen("vault.txt", "r");

	if(fp == NULL)
	{
		printf("File could not be read\n");
	}
	if(fp!=NULL)
	{
		while(fgets())
		char *sample = malloc(sizeof(char *)*length);
		fread(sample, sizeof(char), length, fp);
	}
*/
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

	    int Loop = 1;

	    while(Loop == 1)
	    {
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

		    else if (input1 == 4)
		    {
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
		
	}
	else if((strcmp(adminUsername, inputUsername) != 0) && (strcmp(adminPassword, inputPassword) != 0))
	{
		printMessage2("Invalid admin information");
	}
refresh();
endwin();
return(0);
}

/*to use this example program,  cut/paste any one of the
examples into the main method above.  put it between the comments.
compile and run to see what happens.   You'll have to delete one to try 
the next one*/

/*---------------------------------------
example one
---------------------------------------*/
/*

initscr();	//creates stdscr "std screen"
printw("Hello World");

*/
/*---------------------------------------
example two
---------------------------------------*/
/*

initscr();
for (i=1; i<10; i++)
{
   move(i, i*5);
   printw("Hello World");

}


*/

/*---------------------------------------
example three
---------------------------------------*/
/* 

initscr();
move(4, 15);
printw("Hello World")*/




/*---------------------------------------
example four
---------------------------------------*/

/*

  int rows;
  int cols; 
  char * message;
  char input[5];
  int i;
  int tall;
  int wide;
 
  initscr();
  getmaxyx(stdscr, rows, cols);
  message = "Enter the height ";
  mvprintw(rows-2, 0, "%s", message);
  getstr(input);
  tall = (int)strtol(input, NULL, 10);
  message = "Enter the width    ";
  mvprintw(rows-2, 0, "%s", message);
  getstr(input);
  wide = (int)strtol(input, NULL, 10);
  for (i=0; i<wide; i++)
    {
      mvaddch(0, i, '#');
    }
   for (i=0; i<tall; i++)
   {
     mvaddch(i, 0, '#');
     mvaddch(i, wide, '#');
   }
   for (i=0; i<wide; i++)
    {
      mvaddch(tall, i, '#');
    }


*/