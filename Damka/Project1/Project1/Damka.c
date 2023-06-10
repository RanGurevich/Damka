#include "structs.h"
#include "gameManegment.h"

void main()
{
	Board board = {
	   { ' ', 'T', ' ', 'T', ' ', 'T', ' ', 'T' },
	   { 'T', ' ', 'T', ' ', 'T', ' ', 'T', ' ' },
	   { ' ', 'T', ' ', 'T', ' ', 'T', ' ', 'T' },
	   { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
	   { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
	   { 'B', ' ', 'B', ' ', 'B', ' ', 'B', ' ' },
	   { ' ', 'B', ' ', 'B', ' ', 'B', ' ', 'B' },
	   { 'B', ' ', 'B', ' ', 'B', ' ', 'B', ' ' }
	};

	char player;


	printGameStart(board);
	printf("Please Press T or B for start: ");
	scanf("%c", &player);
	printf("\nThe Initial Board:\n");
	printBoard(board);
	printf("\n");
	printf("===================================================\n\n");
	PlayGame(board, player);

}




