#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "vaultAPI.h"
#define SIZE 50

int main() {

	char * adminUsername = "use";
	char * adminPassword = "pas";
	char inputUsername[20];
	char inputPassword[20];

	initscr();
	cbreak ();

	printMessage2("Admin Username Required:");
	getstr(inputUsername);
	printMessage2("Admin Password Required:");
	noecho ();
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
	    	printMessage1("******************************************************************************");
	    	printMessage1("==============================> Password Vault <==============================");
	    	printMessage1("******************************************************************************");
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
				    		refresh();
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
		    	hashNode * UserNodeInsert = NULL;
		    	UserNodeInsert = malloc(sizeof(hashNode));
		    	DataObject * UserInsert = NULL;
		    	UserInsert = malloc(sizeof(DataObject));
		    	printMessage1("Please enter the key for your password:");
		    	moveTwoY();
		    	moveTwoY();
		    	getstr(buffer3);
		    	removeData(UserDB, buffer3);
		    	moveTwoY();
		    	UserNodeInsert->key = malloc(sizeof(char)*strlen(buffer3)+1);
		    	strcpy(UserNodeInsert->key, input);
		    	UserInsert->systemDescriptor = malloc(sizeof(char)*strlen(buffer3)+1);
		    	strcpy(UserInsert->systemDescriptor, buffer3);
		    	printMessage1("Please enter your new password:");
		    	getstr(buffer3);
		    	moveTwoY();
		    	UserInsert->password = malloc(sizeof(char)*strlen(buffer3)+1); 
		    	strcpy(UserInsert->password, buffer3);
		    	
		    	UserNodeInsert->data = (void*)UserInsert;
		    	
		    	collisionCounter = insertData(UserDB, UserInsert->systemDescriptor, UserNodeInsert->data, collisionCounter);
		    	
		    	moveTwoY();
		    	refresh();
		    }

		    else if (input1 == 4)
		    {
		    	char buffer4[100];
		    	printMessage1("Please enter the key of the password you would like to delete :'(");
		    	getstr(buffer4);
			    if(UserDB->table[UserDB->hashFunction(SIZE, buffer4)] != NULL)
			    {	
			    	moveTwoY();
		    		wprintw(stdscr, buffer4);
		    		moveTwoY();
			    	//moveTwoY();
			    	//removeData(UserDB, input);
			    	//moveTwoY();

		    	}
		    	else if(UserDB->table[UserDB->hashFunction(SIZE, buffer4)] == NULL)
		    	{
		    		moveTwoY();
		    		wprintw(stdscr, "key: %s, doesn't match any passwords.", buffer4);
		    		moveTwoY();
		    	}
		    	refresh();
		    }
		    else if (strcmp(input,"Quit") == 0)
		    {
		    	printMessage1("******************************************************************************");
	    		printMessage1("==============================> Bye For Now :') <==============================");
	    		printMessage1("******************************************************************************");
		    	break;
		    }
		    else
		    {
		    	printMessage1("Invalid Input :'(");
		    	printMessage1("Please try again :')");
		    }
		    refresh();
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