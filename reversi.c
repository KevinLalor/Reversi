//COMP10050 Assignment III - Written by Liam Phelan & Kevin Jardim Lalor
#include "gameIO.h"
#include "gameLogic.h"
#include <stdio.h>

int main(void)
{
	//Initialisation of variables
    player p1 = {"PLAYERONE", NONE, 0, 1};
	player p2 = {"PLAYERTWO", NONE, 0, 1};
	disk board[BOARDSIZE][BOARDSIZE];
	
	//1 indicates it is p1's turn, -1 indicates p2's turn.
	int turnIndicator;
	//Positions on the board
	unsigned int row, col;
	//User is given a press enter to continue confirmation to emphasise if there are no legal moves.
	char enter;
	
	setupPlayer(&p1, &p2);
	setupBoard(board);
	
	//If p1 is black, p1 goes first. Else p2 goes first.
	if (p1.colour == BLACK)
		turnIndicator = 1;
	else
		turnIndicator = -1;
	
	printf("\n--Game Start--\n");
	printBoard(board);
	
	//While the board is not full AND at least one player can make a move AND neither player has lost all their disks: play the game.
	while ((p1.diskCount + p2.diskCount) < 64 && (p1.canMove == 1 || p2.canMove == 1) && (p1.diskCount > 0 && p2.diskCount > 0))
	{
		enter = 0;
		//p1's turn.
		if (turnIndicator == 1)
		{
			//find legal moves.
			p1.canMove = findLegalMoves(board, p1.colour);
			printf("\n");
			
			if (p1.canMove)
			{
				//User choice of legal move.
				printf("%s can move.\nRow: ", p1.name);
				scanf("%1u", &row);
				printf("Col: ");
				scanf("%1u", &col);
				
				//Zero-indexes choice.
				row -= 1;
				col -= 1;
				
				//Catch for bad entry.
				while (!(board[row][col].isLegal))
				{
					printf("That move is illegal.\nRow: ");
					scanf("%1u", &row);
					printf("Col: ");
					scanf("%1u", &col);
					row -= 1;
					col -= 1;
				}
				//Apply Move.
				board[row][col].colour = p1.colour;
				//Flip Disks.
				flipDisks(board, row, col, p1.colour);
			}
			else
			{
				printf("No legal moves for %s.\n", p1.name);
				
				printf("Press enter to continue.\n");
				while (enter != '\r' && enter != '\n')
				{
					enter = getchar(); 
				}
			}
		}
		//p2's turn.
		else
		{
			//find legal moves.
			p2.canMove = findLegalMoves(board, p2.colour);
			printf("\n");
			
			if (p2.canMove)
			{
				//User choice of legal move.
				printf("%s can move.\nRow: ", p2.name);
				scanf("%1u", &row);
				printf("Col: ");
				scanf("%1u", &col);
				
				//Zero-indexes choice.
				row -= 1;
				col -= 1;
				
				//Catch for bad entry.
				while (!(board[row][col].isLegal))
				{
					printf("That move is illegal.\nRow: ");
					scanf("%1u", &row);
					printf("Col: ");
					scanf("%1u", &col);
					row -= 1;
					col -= 1;
				}
				
				//Apply Move.
				board[row][col].colour = p2.colour;
				//Flip disks.
				flipDisks(board, row, col, p2.colour);
			}
			else
			{
				printf("No legal moves for %s.\n", p2.name);
				
				printf("Press enter to continue.\n");
				while (enter != '\r' && enter != '\n') 
				{
					enter = getchar(); 
				}
			}
		}
		
		//Counts player disks/points on board
		countDisks(board, &(p1.diskCount), p1.colour);
		countDisks(board, &(p2.diskCount), p2.colour);
		
		//Swaps turn
		turnIndicator *= -1;
		//Clears old legal moves.
		clearLegalMoves(board);
		
		//Print current board.
		printBoard(board);
		
		//Print current score count.
		printf("%s points: %u\n", p1.name, p1.diskCount);
		printf("%s points: %u\n", p2.name, p2.diskCount);

	}
	
	//Victory/Loss print.
	if(p1.diskCount > p2.diskCount)
	{
		printf("Congratulations %s, you have won!\n", p1.name);
	}
	else if(p1.diskCount < p2.diskCount)
	{
		printf("Congratulations %s, you have won!\n", p2.name);
	}
	else
	{
		printf("Draw!");
	}
	
	//Print result to .txt file.
	printResult(board, p1, p2);
	
    return 0;
}
