//COMP10050 Assignment III - Written by Liam Phelan & Kevin Jardim Lalor
#include <stdio.h>
#include <stdlib.h>
#include "gameIO.h"
#include "gameLogic.h"

//Functions return 1 if a legal move is found, 0 if not.

//Scans board line by line to find disks of the current player's colour.
int findLegalMoves(disk board[BOARDSIZE][BOARDSIZE], enum diskColour playerColour)
{
	unsigned int i, j;
	int canMove = 0;
	
	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			if (board[i][j].colour == playerColour)
			{
				if (checkAround(board, i, j, playerColour) == 1)
					canMove = 1;
			}
		}
	}
	return canMove;
}

//Checks every disk immediately around the disk found by 'findLegalMoves', looking for disks of the opponent's colour.
//offset -1,-1 is equivalent to top left, 1,0 to directly right, etc.
//e.g. top-left of disks around 4,4 is (4-1),(4-1) = 3,3
int checkAround(disk board[BOARDSIZE][BOARDSIZE], unsigned int i, unsigned int j, enum diskColour playerColour)
{
	int iOffset, jOffset, canMove = 0;
	
	for (iOffset = -1; iOffset < 2; iOffset++)
	{
		for (jOffset = -1; jOffset < 2; jOffset++)
		{
			//if space is outside the board, then move on.
			if ((i + iOffset > 7) ||((i + iOffset) < 0) || (j + jOffset) > 7 || ((j + jOffset) < 0))
				continue;
			//if space is the opponent's colour, call net function.
			else if (board[i + iOffset][j + jOffset].colour != playerColour && board[i + iOffset][j + jOffset].colour != NONE)	
			{
				if (checkOut(board, i, j, iOffset, jOffset, playerColour) == 1)
					canMove = 1;
			}
		}
	}
	return canMove;
}

//Checks out in a straight line from disk found in 'checkAround'. If a straight line of opposing disks ending in an empty space is found, then that empty space is a legal move.
int checkOut(disk board[BOARDSIZE][BOARDSIZE], unsigned int i, unsigned int j, int iOffset, int jOffset, enum diskColour playerColour)
{
	size_t x = 0, y = 0;
	
	//'x=0' and 'x=1' have already been confirmed as valid in previous functions.
	//Guard on for loop prevents scanning outside the board (i.e. zero indexed rows and cols greater than 7 and less than 0).
	for (x = 2; !((i + (iOffset * x)) > 7 || (i + (iOffset * x)) < 0) && !((j + (jOffset * x)) > 7 || (j + (jOffset * x)) < 0); x++)
	{
		//if square is empty: found legal move.
		if (board[i + (iOffset * x)][j + (jOffset * x)].colour == NONE)
		{
			//i.e. if this legal move has not already been found.
			if (board[i + (iOffset * x)][j + (jOffset * x)].isLegal == 0)
			{
				printf("%d,%d is valid\n", i + (iOffset * x) + 1, j + (jOffset * x) + 1);
				board[i + (iOffset * x)][j + (jOffset * x)].isLegal = 1;
			}
			//Stores the 'source' of the legal move (the disk found in 'findLegalMoves')
			//These values are used later to flip disks in between that source, and the empty square found in this function.
			//Disks may need to be flipped in up to four different directions, and xSource[4 arrays accomodate this.
			while (board[i + (iOffset * x)][j + (jOffset * x)].iSource[y] != -1)
			{
				y++;
			}
			board[i + (iOffset * x)][j + (jOffset * x)].iSource[y] = i;
			board[i + (iOffset * x)][j + (jOffset * x)].jSource[y] = j;
			return 1;
		}
		//if square is opposing players colour: move out by another multiple of the offset.
		else if (board[i + (iOffset * x)][j + (jOffset * x)].colour != playerColour && board[i + (iOffset * x)][j + (jOffset * x)].colour != NONE)
		{
			continue;
		}
		//if square is the current player's colour: not a legal move, abandon.
		else
		{
			return 0;
		}
	}
}

//Flips the disks inbetween a 'source' disk, and the empty legal space the player wishes to play into.
void flipDisks(disk board[BOARDSIZE][BOARDSIZE], unsigned int row, unsigned int col, enum diskColour currentPlayerColour)
{
	int iDir, jDir, i, j, k;

	//May need to be performed up to four times to flip disks in all four directions.
	//Source values of -1 indicate all relevant disks have been flipped.
	for (k = 0; board[row][col].iSource[k] != -1 && board[row][col].jSource[k] != -1; k++)
	{
		i = 1;
		j = 1;
		if (board[row][col].iSource[k] > row)
			iDir = -1;
		else if (board[row][col].iSource[k] == row)
			iDir = 0;
		else 
			iDir = 1;
		
		if (board[row][col].jSource[k] > col)
			jDir = -1;
		else if (board[row][col].jSource[k] == col)
			jDir = 0;
		else 
			jDir = 1;
		
		//position iSource + (multiple of i-offset), jSource + (multiple of j-offset) is flipped, until end of line is reached.
		for (i = 1, j = 1; board[(board[row][col].iSource[k] + (i * iDir))][(board[row][col].jSource[k] + (j * jDir))].colour != currentPlayerColour; i++, j++)
			board[(board[row][col].iSource[k] + (i * iDir))][(board[row][col].jSource[k] + (j * jDir))].colour = currentPlayerColour;
		
	}
}

//Clears all legal move values to start clean on the next turn.
void clearLegalMoves(disk board[BOARDSIZE][BOARDSIZE])
{
	size_t i, j, k;
	
	for (i = 0; i < BOARDSIZE; i++)
	{
		for (j = 0; j < BOARDSIZE; j++)
		{
			board[i][j].isLegal = 0;
			for (k = 0; k < 4; k++)
			{
				board[i][j].iSource[k] = -1;
				board[i][j].jSource[k] = -1;
			}
		}
	}
}

//Counts the number of disks of a given player currently on the board.
void countDisks(disk board[BOARDSIZE][BOARDSIZE], unsigned int *disks, enum diskColour playerColour)
{
	size_t i, j;
	
	*disks = 0;
	
	for (i = 0; i < BOARDSIZE; i++)
	{
		for (j = 0; j < BOARDSIZE; j++)
		{
			if (board[i][j].colour == playerColour)
				(*disks)++;
		}
	}
}
