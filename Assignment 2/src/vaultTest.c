#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "vaultAPI.h"
#define SIZE 50

int main() {

//initscr();
//move(4, 15);
//printw("Hello World");

	int collisionCounter = 0;
	HTable * UserDB;
	UserDB = createTable(SIZE, &hashFunction, &deleteData, &printData);
	//int rows;
    //int cols; 
    char * message;
    char input[100];
    int input1;
    //char * password;
    int Loop = 1;
    //int tall;
    //int wide;
 
    initscr();
    while(Loop == 1)
    {
	    message = "Select one of the following, by entering the corresponding value in it's brackets:\n";
	    printw(message);
	    message = "-> (1) Store Password\n";
	    printw(message);
	    message = "-> (2) Retrieve Password\n";
	    printw(message);
	    message = "-> (3) Change Password\n";
	    printw(message);
	    message = "-> (4) Delete Password\n";
	    printw(message);
	    message = "-> (Quit) Quit\n";
	    printw(message);
	    printw("\n");
	    getstr(input);
	    printw("\n");
	    input1 = (int)strtol(input, NULL, 10);
	    printw("\n\n");
	    if (input1 == 1)
	    {
	    	hashNode * UserNodeInsert = NULL;
	    	UserNodeInsert = malloc(sizeof(hashNode));
	    	DataObject * UserInsert = NULL;
	    	UserInsert = malloc(sizeof(DataObject));
	    	printw("Please create/enter a key for your account :)\n");
	    	printw("\n");
	    	getstr(input);
	    	printw("\n");
	    	UserNodeInsert->key = malloc(sizeof(char)*strlen(input)+1);
	    	strcpy(UserNodeInsert->key, input);
	    	UserInsert->systemDescriptor = malloc(sizeof(char)*strlen(input)+1);
	    	strcpy(UserInsert->systemDescriptor, input);
	    	printw("Please enter the password you would like to store:\n");
	    	printw("\n");
	    	getstr(input);
	    	printw("\n");
	    	UserInsert->password = malloc(sizeof(char)*strlen(input)+1); 
	    	strcpy(UserInsert->password, input);
	    	
	    	UserNodeInsert->data = (void*)UserInsert;
	    	
	    	collisionCounter = insertData(UserDB, UserInsert->systemDescriptor, UserNodeInsert->data, collisionCounter);
	    	
	    	printw("\n");
	    }
	    else if (input1 == 2)
	    {
	    	
	    	printw("Please enter your key :D\n");
	    	printw("\n");
	    	getstr(input);
	    	printw("\n");
	    	if(UserDB->table[hashFunction(UserDB->tableSize, input)] == NULL)
	    	{
	    		printw("\nKey: ");
	    		printw(input);
	    		printw(" doesn't match any passwords sorry :'(\n");
	    	}
	    	if(UserDB->table[hashFunction(UserDB->tableSize, input)] != NULL)
		    {	
		    	hashNode * UserNodeOutput = NULL;
		    	DataObject * UserOutput = NULL;
		    	DataObject * UserCheck = NULL;
		    	UserNodeOutput = malloc(sizeof(hashNode));
		    	UserOutput = malloc(sizeof(DataObject));
		    	UserCheck = malloc(sizeof(DataObject));
		    	UserCheck = UserDB->table[UserDB->hashFunction(SIZE, input)]->data;
		    	UserOutput = lookupData(UserDB, input);
		    	UserNodeOutput->data = (void*)UserOutput;

		    	if(UserDB->table[UserDB->hashFunction(SIZE, UserCheck->systemDescriptor)] != NULL)
			    {
			    	if((UserOutput->password != NULL) && (UserOutput->systemDescriptor != NULL))
			    	{
			    		printw("\nSaved Password-> %s\n\n", UserOutput->password);
			    		printw("\n");
			    	}
			    }
			}
	    	else
	    	{
	    		printw("\n\nPassword not found :$\n\n");
	    	}
	    	printw("\n\n\n");
	    }
	    else if (input1 == 3)
	    {
	    	hashNode * UserNodeInsert = NULL;
	    	UserNodeInsert = malloc(sizeof(hashNode));
	    	DataObject * UserInsert = NULL;
	    	UserInsert = malloc(sizeof(DataObject));
	    	printw("Please enter the key for your password:\n");
	    	printw("\n");
	    	getstr(input);
	    	printw("\n");
	    	printw("\n");
	    	removeData(UserDB, input);
	    	printw("\n");
	    	UserNodeInsert->key = malloc(sizeof(char)*strlen(input)+1);
	    	strcpy(UserNodeInsert->key, input);
	    	UserInsert->systemDescriptor = malloc(sizeof(char)*strlen(input)+1);
	    	strcpy(UserInsert->systemDescriptor, input);
	    	printw("Please enter your new password:\n");
	    	printw("\n");
	    	getstr(input);
	    	printw("\n");
	    	UserInsert->password = malloc(sizeof(char)*strlen(input)+1); 
	    	strcpy(UserInsert->password, input);
	    	
	    	UserNodeInsert->data = (void*)UserInsert;
	    	
	    	collisionCounter = insertData(UserDB, UserInsert->systemDescriptor, UserNodeInsert->data, collisionCounter);
	    	
	    	printw("\n");
	    }
	    else if (input1 == 4)
	    {
	    	printw("Please enter the password of the account you would like to delete :'(\n");
	    	printw("\n");
	    	getstr(input);
	    	printw("\n");
	    	removeData(UserDB, input);
	    	printw("\n");
	    }
	    else if (strcmp(input,"Quit") == 0)
	    {
	    	printf("\nBye Bye :)\n");
	    	break;
	    }
	    else
	    {
	    	printw("Invalid Input :'(\n\n");
	    	printw("Please try again :')\n\n\n\n");
	    }
	}

refresh();
getch(); //does nothing except wait for you to press a character so you can see the results on the screen
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