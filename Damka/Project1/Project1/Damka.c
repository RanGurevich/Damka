#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "structs.h"
#include "boardAndMovements.h"


void main()
{

	Board board = {
	   { ' ', ' ', ' ', 'B', ' ', ' ', ' ', 'B' },
	   { 'B', ' ', 'B', ' ', 'B', ' ', 'B', ' ' },
	   { ' ', 'B', ' ', ' ', ' ', 'B', ' ', ' ' },
	   { ' ', ' ', ' ', ' ', 'B', ' ', 'B', ' ' },
	   { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
	   { 'T', ' ', 'T', ' ', 'B', ' ', 'T', ' ' },
	   { ' ', 'T', ' ', 'T', ' ', 'T', ' ', 'T' },
	   { 'T', ' ', 'T', ' ', 'T', ' ', 'T', ' ' }
	};

	checkersPos src = {'G', '3'};

	printf("Initial Board:\n");
	printBoard(board);
	printf("\n");

	SingleSourceMovesTree* tree = FindSingleSourceMove(board, &src);

	//printf("Board after Operations:\n");
	//printBoard(tree->source->next_move[1]->board);
	//printf("\n");

}

