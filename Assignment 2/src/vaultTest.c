#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "vaultAPI.h"
#define SIZE 50

int main() {

	char * adminUsername = "username";
	char * adminPassword = "password";
	char inputUsername[20];
	char inputPassword[20];

	initscr();

	printMessage2("Admin Username Required:");
	getstr(inputUsername);
	printMessage2("Admin Password Required:");
	getstr(inputPassword);
	if((strcmp(adminUsername, inputUsername) == 0) && (strcmp(adminPassword, inputPassword) == 0))
	{
		int collisionCounter = 0;
		HTable * UserDB;
		UserDB = createTable(SIZE, &hashFunction, &deleteData, &printData);
	    char * message;
	    char input[100];
	    int input1;
	    int Loop = 1;

	    while(Loop == 1)
	    {
		    message = "Select one of the following, by entering the corresponding value in it's brackets:\n";
		    printMessage1(message);
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
		    moveTwoY();
		    getstr(input);
		    input1 = (int)strtol(input, NULL, 10);
		    if(input1 == 1)
		    {
		    	hashNode * UserNodeInsert = NULL;
		    	UserNodeInsert = malloc(sizeof(hashNode));
		    	DataObject * UserInsert = NULL;
		    	UserInsert = malloc(sizeof(DataObject));
		    	printMessage1("Please create/enter a key for your account :)");
		    	moveTwoY();
		    	getstr(input);
		    	UserNodeInsert->key = malloc(sizeof(char)*strlen(input)+1);
		    	strcpy(UserNodeInsert->key, input);
		    	UserInsert->systemDescriptor = malloc(sizeof(char)*strlen(input)+1);
		    	strcpy(UserInsert->systemDescriptor, input);
		    	printMessage1("Please enter the password you would like to store:");
		    	moveTwoY();
		    	getstr(input);
		    	UserInsert->password = malloc(sizeof(char)*strlen(input)+1); 
		    	strcpy(UserInsert->password, input);
		    	
		    	UserNodeInsert->data = (void*)UserInsert;
		    	
		    	collisionCounter = insertData(UserDB, UserInsert->systemDescriptor, UserNodeInsert->data, collisionCounter);
		    }
		    else if(input1 == 2)
		    {
		    	printMessage1("Please enter your key:");
		    	moveTwoY();
		    	moveTwoY();
		    	getstr(input);
		    	wmove(stdscr, 2, 0);
		    	if(UserDB->table[hashFunction(UserDB->tableSize, input)] == NULL)
		    	{
		    		wprintw(stdscr, "Key: %s doesn't match any passwords sorry :'(", input);
		    		refresh();
		    		moveTwoY();
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
				    		wprintw(stdscr, "Saved Password-> %s", UserOutput->password);
				    		refresh();
				    		moveTwoY();
				    	}
				    }
				}
		    	else
		    	{
		    		printMessage2("Password not found :$");
		    	}
		    	moveTwoY();
		    }
		    else if (input1 == 3)
		    {
		    	hashNode * UserNodeInsert = NULL;
		    	UserNodeInsert = malloc(sizeof(hashNode));
		    	DataObject * UserInsert = NULL;
		    	UserInsert = malloc(sizeof(DataObject));
		    	printMessage1("Please enter the key for your password:");
		    	moveTwoY();
		    	moveTwoY();
		    	getstr(input);
		    	removeData(UserDB, input);
		    	moveTwoY();
		    	UserNodeInsert->key = malloc(sizeof(char)*strlen(input)+1);
		    	strcpy(UserNodeInsert->key, input);
		    	UserInsert->systemDescriptor = malloc(sizeof(char)*strlen(input)+1);
		    	strcpy(UserInsert->systemDescriptor, input);
		    	printMessage1("Please enter your new password:");
		    	getstr(input);
		    	moveTwoY();
		    	UserInsert->password = malloc(sizeof(char)*strlen(input)+1); 
		    	strcpy(UserInsert->password, input);
		    	
		    	UserNodeInsert->data = (void*)UserInsert;
		    	
		    	collisionCounter = insertData(UserDB, UserInsert->systemDescriptor, UserNodeInsert->data, collisionCounter);
		    	
		    	moveTwoY();
		    }

		    else if (input1 == 4)
		    {
		    	printMessage1("Please enter the password of the account you would like to delete :'(");
		    	getstr(input);
		    	moveTwoY();
		    	removeData(UserDB, input);
		    	moveTwoY();
		    }
		    else if (strcmp(input,"Quit") == 0)
		    {
		    	printMessage2("Bye Bye :)");
		    	break;
		    }
		    else
		    {
		    	printMessage1("Invalid Input :'(");
		    	printMessage1("Please try again :')");
		    }
		}
		
	}
	else if((strcmp(adminUsername, inputUsername) != 0) && (strcmp(adminPassword, inputPassword) != 0))
	{
		printMessage2("Invalid admin information");
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