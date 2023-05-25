#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "structs.h"
#include "boardAndMovements.h"


void main()
{

	Board board = {
	   { ' ', 'B', ' ', 'B', ' ', 'B', ' ', 'B' },
	   { 'B', ' ', 'B', ' ', 'B', ' ', 'B', ' ' },
	   { ' ', 'B', ' ', 'B', ' ', 'B', ' ', 'B' },
	   { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
	   { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
	   { 'T', ' ', 'E', ' ', 'T', ' ', 'T', ' ' },
	   { ' ', 'T', ' ', 'T', ' ', 'T', ' ', 'T' },
	   { 'T', ' ', 'T', ' ', 'T', ' ', 'T', ' ' }
	};

	checkersPos src = {'5', 'C'};

	printf("Initial Board:\n");
	printBoard(board);
	printf("\n");

	printf("%c", getCharOnBoard(board, &src));

//	SingleSourceMovesTree* tree = FindSingleSourceMove(board, &src);

	/*printf("Board after Operations:\n");
	printBoard(tree->source->board);
	printf("\n");*/

}

