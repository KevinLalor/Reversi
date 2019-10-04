//COMP10050 Assignment III - Written by Liam Phelan & Kevin Jardim Lalor
#include <stddef.h>

//See .c file for function comments.

int findLegalMoves(disk board[BOARDSIZE][BOARDSIZE], enum diskColour playerColour);
int checkAround(disk board[BOARDSIZE][BOARDSIZE], unsigned int i, unsigned int j, enum diskColour playerColour);
int checkOut(disk board[BOARDSIZE][BOARDSIZE], unsigned int i, unsigned int j, int iOffset, int jOffset, enum diskColour playerColour);

void flipDisks(disk board[BOARDSIZE][BOARDSIZE], unsigned int row, unsigned int col, enum diskColour currentPlayerColour);

void clearLegalMoves(disk board[BOARDSIZE][BOARDSIZE]);

void countDisks(disk board[BOARDSIZE][BOARDSIZE], unsigned int *disks, enum diskColour playerColour);

