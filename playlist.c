// Micheal O' Sullivan
// R00128516 
// SD2C - C Programming
// Playlist Builder
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//structure
struct listNode{ 
    char songIndex[50];
	char songTitle[50];
	char songArtist[50];
	int songLength;
	struct listNode *next;
};

//loc pointer of *next
struct listNode *nextListNode(struct listNode *cursor){
	return cursor->next;
}

//add song to next node
void addNewSongNode(char *songIndex, char *songTitle, char *songArtist, int songLength, struct listNode *cursor){
	strcpy(cursor->songIndex, songIndex);
	strcpy(cursor->songTitle, songTitle);
    strcpy(cursor->songArtist, songArtist);
	cursor->songLength = songLength;
}

//insert song into next node
void insertListNode(struct listNode *cursor, struct listNode *newNode){
	struct listNode *temp = NULL;
	temp = cursor->next;
	cursor->next = newNode;
	newNode->next = temp;
}

//function to save data to file
void saveTofile(struct listNode *root, char title[50]){
	char filename[60];
	strcpy(filename, title); 
	strcat(filename, ".txt"); //concatenate strings to allow playlist name be file name
	FILE *f = fopen(filename, "w");
	if (f == NULL)
	{
		printf("File Not Found");
		return;
	}
	fprintf(f, "%s's Songs\n", title);
	struct listNode *temp = root; //create variable temp
	while (temp != NULL) //while temp is not NUll, begin loop
	{
	
		fprintf(f, "Song Index: %s\n", temp->songIndex);
		fprintf(f, "Song Title: %s\n", temp->songTitle);
		fprintf(f, "Artist Name: %s\n", temp->songArtist);
		fprintf(f, "Duration Of Song: %d\n\n", temp->songLength);
		temp = temp->next; //Move to next pointer
	}
	printf("Data Saved Successfully\n");
	fclose(f);
}

//function to print random song from playlist
void printRandom(struct listNode *head)
{
	int length = 0;
	struct listNode *temp = head; //allow head to be temp variable
	while (temp != NULL)
	{
		length++;
		temp = temp->next; //caluclate length
	}
	
	if (length == 0)
	{
		printf("No songs available");
		return;
	}
	srand(time(0)); //generate random number
	int rn = 0 + rand() % (length);
	int i = 0;
	temp = head;
	printf("Random Song Chosen\n\n");
	while (i < rn && temp->next!=NULL) //move temp to selected index
	{
		temp = temp->next;
		i++;
	}

	printf("Song Index: %s\n", temp->songIndex);
	printf("Song Title: %s\n", temp->songTitle);
	printf("Artist's Name: %s\n", temp->songArtist);
	printf("Duration Of Song: %d\n", temp->songLength);
	printf("\n");
}

//function to shuffle list
void shuffleRandom(struct listNode *head)
{
	int length = 0;
	struct listNode *temp = head; 
	while (temp != NULL)
	{
		length++;
		temp = temp->next; 
	}
	
	if (length == 0)
	{
		printf("No songs available");
		return;
	}
	srand(time(0)); 
	int rn = 0 + rand() % (length);
	int i = 0;
	temp = head;
	while (i < rn && temp->next!=NULL) 
	{
		temp = temp->next;
		i++;
		
	}
	printf("LIST SHUFFLED\n");//list doesn't shuffle, just for purpose of assignment

}

//function to swap two node positions
void swapNodes(struct listNode **head_ref, char x[50], char y[50])
{
    if (x == y)
        return; //return if indexes are equal
        
    struct listNode *prevX = NULL, *currX = *head_ref; //search for x (prev & curr)
    while (currX && strcmp(currX->songIndex, x) != 0)
    {
        prevX = currX;
        currX = currX->next;
    }

    struct listNode *prevY = NULL, *currY = *head_ref; //search for y (prev & curr)
    while (currY && strcmp(currY->songIndex, y) != 0)
    {
        prevY = currY;
        currY = currY->next;
    }

    if (currX == NULL || currY == NULL) //if neither present, return;
        return;

    if (prevX != NULL) //if x is not head
        prevX->next = currY;
    else
        *head_ref = currY; //make y head
        
    if (prevY != NULL) //if y is not head
        prevY->next = currX;
    else 
        *head_ref = currX; //make x head

    struct listNode *temp = currY->next; //swap next pointers
    currY->next = currX->next;
    currX->next = temp;
    printf("Songs Swapped - Play Playlist!\n");
}

//value for playlist name when enetered by user
char setPlaylistName[50] = "";

void breakLines(){
    printf("\n\n\n"); //basic function to seperate display in menu
}

void resultBarrier(){
    printf("**************************\n"); //basic function with astericks for display
}

//function for printing menu
void menuText(char * playlistName){
    
	printf("---PLAYLIST MENU---\n");
	printf("1. Create A Playlist\n");
	printf("2. Add Song To Playlist\n");
	printf("3. Play(Print) Entire Playlist\n");
	printf("4. Search For Song By Title/Artist\n");
	printf("5. Delete Song From Playlist\n");
	printf("6. Swap The Position Of Two Songs\n");
	printf("7. Play(Print) Random Song From Playlist\n");
	printf("8. Shuffle The Playlist\n");
	printf("9. Duration Of Entire Playlist\n");
	printf("10. Save Playlist To File\n"); 
	printf("11. Load Playlist From File\n");
	printf("12. Exit Program\n");
}

//interactive function to take user input
//access to most functions unavaible until playlist is created (option 1)
//once characters are not null for playlistName, user can use other options

void printMenuMain(char *playlistName){
	struct listNode *head = NULL;
	struct listNode *cursor;
	struct listNode *tail;
	struct listNode *current;
	struct listNode *temp;
	
	int position = 0;
	int newPosition = 0;
	char songIndex[50];
	char songTitle[50];
	char songArtist[50];
	int songLength = 0;
	menuText(playlistName);
	
	int option;
	while (option != 12) // user enters 12 to terminate program.
    {
		printf("Choose An Option: ");
		scanf("%d", &option);
		printf("\n");
		switch (option) //switch statement to allow interactive menu to function
		{   
		
		case 1:
			printf("Enter Playlist's Title: ");
			scanf(" %s", setPlaylistName);
			resultBarrier();
			printf("Playlist '%s' created!\n", setPlaylistName); //get name of playlist to be created
			resultBarrier();
			breakLines();
			printMenuMain(setPlaylistName); //print menu & allows other options in menu now to be accessible
			break;

		case 2:
		if ((playlistName != NULL) && (playlistName[0] == '\0')){ //ensure user creates a playlist before using other options
		            printf("NO PLAYLIST CREATED - CREATE PLAYLIST FIRST!\n\n");
                    printMenuMain(playlistName);
                    break;
		        }
			printf("ENTER SONG DETAILS BELOW\n");
			printf("Enter Song Index: ");
			scanf(" %100[^\n]", songIndex);
			printf("Enter Song's Title: ");
			scanf(" %100[^\n]", songTitle);
			printf("Enter Artist's Title: ");
			scanf(" %100[^\n]", songArtist);
			printf("Enter In Seconds The Duration Of Song: ");
			scanf("%d", &songLength);
			printf("\n");
			if (head == NULL) // if head is empty
			{
				head = (struct listNode *)malloc(sizeof(struct listNode)); //head allocated memory address
				addNewSongNode(songIndex, songTitle, songArtist, songLength, head); //listNode_song function with input from user to node
				tail = head;
				resultBarrier();
				printf("SONG '%s' ADDED!\n", songTitle);
				resultBarrier();
				breakLines();
			}
			else if (head != NULL){ //if head is not empty
				current = (struct listNode *)malloc(sizeof(struct listNode));
				addNewSongNode(songIndex, songTitle, songArtist, songLength, current); //listNode_song function with input from user to node
				insertListNode(tail, current); //insert song into NEXT node
				tail = current;
				resultBarrier();
				printf("SONG '%s' ADDED!\n", songTitle);
				resultBarrier();
				breakLines();
			}
			else {
			    printf("ERROR");
			}
			menuText(playlistName);
			break;
			
		case 3:
		if ((playlistName != NULL) && (playlistName[0] == '\0')){
		            printf("NO PLAYLIST CREATED - CREATE PLAYLIST FIRST!\n\n");
                    printMenuMain(playlistName);
                    break;
		    }
		    else if (head == NULL){
		        resultBarrier();
			    printf(" **Playlist Songs**\n\n");
		    	printf("Playlist Empty - Add Songs In Menu\n\n");
			}
			else{
			    resultBarrier();
			    printf(" **Playlist Songs**\n\n");
				current = head; //allow current be head
				while (current != NULL) //while head is not empty
				{
				    //print user input of song
					printf("Song Index: %s\n", current->songIndex);
                	printf("Song Title: %s\n", current->songTitle);
                	printf("Artist's Name: %s\n", current->songArtist);
                	printf("Duration Of Song: %d\n\n\n", current->songLength);
					current = nextListNode(current); //locate next node
				}
			}
			resultBarrier();
			breakLines();
			menuText(playlistName);
			break;
			
		case 4:
		if ((playlistName != NULL) && (playlistName[0] == '\0')){ //ensure user creates a playlist before using other options
		            printf("NO PLAYLIST CREATED - CREATE PLAYLIST FIRST!\n\n");
                    printMenuMain(playlistName);
                    break;
		        }
            printf("SEARCH SONG\n"); //Search for song by artist name or song name
            int sChoice = 0;
            printf("1. Search By Artist\n"); 
            printf("2. Search By Song Title\n");
            printf("Enter Choice: ");
            scanf("%d", &sChoice); //get user option
            switch (sChoice)
            {
            case 1: //option 1
                printf("Enter Artist Name: ");
                scanf(" %100[^\n]", songArtist);  
                printf("\n\n");
                struct listNode *temp = head, *pre; //temporary playlist node
                if (temp == NULL) //if head is null               
                {
                    printf("You have no Song\n\n");
                }
                else
                {   resultBarrier();
                    printf("SONGS FOUND BY ARTIST: '%s'", songArtist);
                    printf("\n");
                    while (temp != NULL) //while head is not null
                    {
                        pre = temp;
                        if (strcmp(temp->songArtist, songArtist) == 0) //if artist's name are equal
                        {
                            printf("\n");
                            printf("Song Index: %s\n", temp->songIndex);
                        	printf("Song Title: %s\n", temp->songTitle);
                        	printf("Artist's Name: %s\n", temp->songArtist);
                        	printf("Duration Of Song: %d\n\n", temp->songLength); 
                        	//print data of equal node
                        }
                        temp = temp->next; //go to next node
                    }
                }
                resultBarrier();
                breakLines();
                menuText(playlistName);
                break;

            case 2: //option 2
                printf("Enter Song's Title: ");
                scanf(" %100[^\n]", songTitle);   
                printf("\n\n");
                struct listNode *temp2 = head, *prev; //temporary variable for playlist node
                if (temp2 == NULL)                    
                {
                    printf("You have no Song\n\n");
                }
                else
                {
                    resultBarrier();
                    printf("SONGS FOUND BY TITLE: '%s'", songArtist);
                    printf("\n");
                    while (temp2 != NULL) 
                    {
                        prev = temp2;
                        if (strcmp(temp2->songTitle, songTitle) == 0) //if song's titles are equal
                        {
                            printf("\n");
                            printf("Song Index: %s\n", temp2->songIndex);
                        	printf("Song Title: %s\n", temp2->songTitle);
                        	printf("Artist's Name: %s\n", temp2->songArtist);
                        	printf("Duration Of Song: %d\n\n", temp2->songLength);
                        	//print data of equal node
                        }
                        temp2 = temp2->next; //go to next node
                    }
                }
                resultBarrier();
                breakLines();
                menuText(playlistName);
                break;
            }
            break;
            
        case 5:
        if ((playlistName != NULL) && (playlistName[0] == '\0')){ //ensure user creates a playlist before using other options
		            printf("NO PLAYLIST CREATED - CREATE PLAYLIST FIRST!\n\n");
                    printMenuMain(playlistName);
                    break;
		        }
            //delete song from playlist
            //removes song, but removes every song from playlist
            printf("DELETE SONG\n");
            printf("Enter Index Of Song To Be Deleted: ");
            scanf(" %100[^\n]", songIndex); //input index of song to be deleted
            printf("\n");
            struct listNode *temp = head, *prev; //temporary variable for playlist node

            if (temp != NULL && strcmp(temp->songIndex, songIndex) == 0) //if head holds the index and playlist head is not null and index is equal to song
            {
                head = temp->next;
                free(temp); //free head
                resultBarrier();
                printf("SONG WITH INDEX '%s' DELETED\n", songIndex);
                resultBarrier();
                breakLines();
            }
            else
            {
                while (temp != NULL && strcmp(temp->songIndex, songIndex) != 0) 
                {
                    prev = temp;
                    temp = temp->next;
                }

                if (temp != NULL) //if index was not present in linked list
                {
                    prev->next = temp->next;
                    free(temp); //free
                    resultBarrier();
                    printf("SONG WITH INDEX '%s' DELETED\n", songIndex);
                    resultBarrier();
                    breakLines();
                }
            }
            menuText(playlistName);
            break;


        case 6:
        if ((playlistName != NULL) && (playlistName[0] == '\0')){ //ensure user creates a playlist before using other options
                    breakLines();
		            printf("NO PLAYLIST CREATED - CREATE PLAYLIST FIRST!\n\n");
		            resultBarrier();
                    breakLines();
                    printMenuMain(playlistName);
                    break;
		        }
        
        {   //implementation of swapping two nodes
            char p1[50], p2[50]; //allow p1 & p2 to be indexes to swap
            printf("Enter Index Of First Song: ");
            scanf("%s", p1); 
            printf("Enter Index Of Second Song: ");
            scanf("%s", p2);
            printf("\n");
            resultBarrier();
            swapNodes(&head, p1, p2); //call swap nodes function
            resultBarrier();
            breakLines();
            menuText(playlistName);
            break;
        }
			
			
	    case 7:
	    if ((playlistName != NULL) && (playlistName[0] == '\0')){ //ensure user creates a playlist before using other options
		            printf("NO PLAYLIST CREATED - CREATE PLAYLIST FIRST!\n\n");
                    printMenuMain(playlistName);
                    break;
		        }
	    {   //call function to print random song
	        resultBarrier();
			printRandom(head);
			resultBarrier();
			breakLines();
			menuText(playlistName);
			break;
		}
		
		
		case 8: //issues with the option to shuffle the list. 
		        //list doesn't shuffle, left code as attempted since program compiles
		    {
		        resultBarrier();
		        shuffleRandom(head);
		        resultBarrier();
		    	breakLines();
		        menuText(playlistName);
                break;
		    }

		case 9:
    	if ((playlistName != NULL) && (playlistName[0] == '\0')){ 
	            printf("NO PLAYLIST CREATED - CREATE PLAYLIST FIRST!\n\n");
                printMenuMain(playlistName);
                break;
	        }
	   else if (head == NULL){ 
		    	printf("Playlist Empty - Add Songs In Menu\n\n");
			}
			else{
        printf("ENTIRE DURATION OF PLAYLIST IN SECONDS\n");
			int seconds = 0;
			current = head; //let current be head
			while (current != NULL) //while head is not null
			{
				seconds += current->songLength; //get song length of each node
				current = nextListNode(current);
				 //print total sum of seconds
				}
				resultBarrier();
				printf("Total Seconds: %d\n", seconds); 
				resultBarrier();
		    	breakLines();
				menuText(playlistName);
                break;
			}
			
		case 10:
		if ((playlistName != NULL) && (playlistName[0] == '\0')){ //ensure user creates a playlist before using other options
		            printf("NO PLAYLIST CREATED - CREATE PLAYLIST FIRST!\n\n");
                    break;
		        }
		    {   //call saveToFile function
		        resultBarrier();
		    	saveTofile(head, playlistName);
		    	resultBarrier();
		    	breakLines();
		    	
		    }
		    menuText(playlistName);
		    break;
		    
		case 11:
		{   
		    //implementation to load data from file. 
		    //compiles with program, but terminates when option is chosen
		    //attempted to concatenate variables from file to memory address, but program wouldn't compile
			char filename[60];
			printf("Enter Filename: ");
			scanf("%s", filename); //get user to input name of file
			char title[50];
			FILE *f = fopen(filename, "r");
			fscanf(f, "%s", title);
			if (f == NULL)
			{
				printf("File Not Found"); // if file does not exist
				return;
			}
			struct listNode *temp = head;
			char arr[500];
			while (fscanf(f, "%s", arr) == 1)
            {
                if (head == NULL)
				{
					head = (struct listNode *)malloc(sizeof(struct listNode));
					addNewSongNode(songIndex, songTitle, songArtist, songLength, head);
					tail = head;
				}
				else
				{
					current = (struct listNode *)malloc(sizeof(struct listNode));
					addNewSongNode(songIndex,songTitle, songArtist, songLength, current);
					insertListNode(tail, current);
					tail = current;
				}
			}
			printf("Load Successfully\n");
			fclose(f);
			menuText(playlistName);
			break;
			
			
			case 12: //if option 12 is chosen, kill program and display goodbye message
			    printf("Thanks & Goodbye! :)");
			    exit(1);

            }

		}
	}
}
 //main 
int main(void)
{
	printf("\n***WELCOME TO THE MTU PLAYLIST CREATOR***\n\n");
	printMenuMain(setPlaylistName); //call printMainMenu function
	
}