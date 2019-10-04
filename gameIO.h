//COMP10050 Assignment III - Written by Liam Phelan & Kevin Jardim Lalor
#define NAMESIZELIMIT 20
#define BOARDSIZE 8

//Represents white & black disks, and empty spaces on the board.
enum diskColour
{
	WHITE,
	BLACK,
	NONE
};

//Contains player name, colour, and number of disks/points.
typedef struct player
{
    char name[NAMESIZELIMIT];
	enum diskColour colour;
    unsigned int diskCount, canMove;
} player;

//Represents a space on the board.
//Contains disk colour, whether the space is legal move or not, and 'source' of disk flips (see comments in 'gameLogic.c' for more info).
typedef struct disk
{
	enum diskColour colour;
	unsigned int isLegal;
	int iSource[8], jSource[8];
} disk;

void setupPlayer(player *p1, player *p2);

void setupBoard(disk board[BOARDSIZE][BOARDSIZE]);

void printBoard(disk board[BOARDSIZE][BOARDSIZE]);

//prints results
void printResult(disk board[BOARDSIZE][BOARDSIZE], player p1, player p2);
