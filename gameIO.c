//COMP10050 Assignment III - Written by Liam Phelan & Kevin Jardim Lalor
#include <stdio.h>
#include "gameIO.h"

//Initialisation of players.
void setupPlayer(player *p1, player *p2)
{
    int colourChoice;

    printf("Player 1 Name: ");
    scanf("%20s", p1->name);
    printf("Player 2 Name: ");
    scanf("%20s", p2->name);
	printf("\n");

    printf("%s, enter 1 to play as Black or any other number to play as White.\n%s will default to the opposite.\nChoice: ", p1->name, p2->name);
    scanf("%d", &colourChoice);

    if (colourChoice == 1)
    {
        p1->colour = BLACK;
        p2->colour = WHITE;
    }
    else if (!(colourChoice == 1))
    {
        p1->colour = WHITE;
        p2->colour = BLACK;
    }

    //Game starts with two of each counter in the centre of the board.
    p1->diskCount = 2;
    p2->diskCount = 2;
}

//Initialisation of Board.
void setupBoard(disk board[BOARDSIZE][BOARDSIZE])
{
    size_t i, j, k;

    //'Fills' the board with empty spaces.
    for (i = 0; i < BOARDSIZE; i++)
    {
        for (j = 0; j < BOARDSIZE; j++)
		{
          	board[i][j].colour = NONE;
			board[i][j].isLegal = 0;
			for (k = 0; k < 4; k++)
			{
				board[i][j].iSource[k] = -1;
				board[i][j].jSource[k] = -1;
			}
		}
    }

    //Four central squares always contain two White and two Black counters at the start of the game.
	board[3][3].colour = WHITE;
    board[3][4].colour = BLACK;
    board[4][3].colour = BLACK;
    board[4][4].colour = WHITE;
}

//Prints the current layout of the board.
void printBoard(disk board[BOARDSIZE][BOARDSIZE])
{
    size_t i, j;
	
	printf("\n   1 2 3 4 5 6 7 8\n\n");
	for (i = 0; i < BOARDSIZE; i++)
	{
		printf("%d  ", i + 1);
		for (j = 0; j < BOARDSIZE; j++)
		{
			if (board[i][j].colour == WHITE)
				printf("1 ");
			else if (board[i][j].colour == BLACK)
				printf("0 ");
			else
				printf("x ");
		}
		printf("\n");
	}
	printf("\n");
}

//Writes the current standing of the game to a results plain text file.
void printResult(disk board[BOARDSIZE][BOARDSIZE], player p1, player p2)
{
    FILE *cfPtr; // pointer to student.txt

    
    //Cancel if unable to create file
	//Appends, to allow multiple game results to be saved and reviewed.
    if((cfPtr = fopen("reversiResults.txt", "a")) == NULL) 
    {
        puts("File could not be opened");
    }
    else 
    {
        //Separate printf in main while loop for printing to console after every move to track score in-game.
        //stored in 'reversiResults.txt'
        fprintf(cfPtr, "Player 1: %s, points: %d\n", p1.name, p1.diskCount);
        fprintf(cfPtr, "Player 2: %s, points: %d\n\n", p2.name, p2.diskCount);
    }
    fclose(cfPtr);
}