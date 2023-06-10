#include "Structs.h"
#include "GameManegment.h"

void main()
{
	Board board = 
	{
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

	while (player != PLAYER_T && player != PLAYER_B)
	{
		printf("Sorry, your input is not valid\nPlease Try Again\n\n");
		scanf(" %c", &player);
	}

	printf("\nThe Initial Board:\n");
	printBoard(board);
	printf("\n");
	printf("===================================================\n\n");
	PlayGame(board, player);

}