#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "structs.h"
#include "boardAndMovements.h"
#include "movements.h"

//void printList(SingleSourceMovesList* lst);


void main()
{

	Board board = {
	   { ' ', ' ', ' ', 'B', ' ', ' ', ' ', 'B' },
	   { 'B', ' ', 'B', ' ', 'B', ' ', ' ', ' ' },
	   { ' ', 'B', ' ', ' ', ' ', 'B', ' ', ' ' },
	   { ' ', ' ', ' ', ' ', ' ', ' ', 'B', ' ' },
	   { ' ', ' ', ' ', 'E ', ' ', ' ', ' ', ' ' },
	   { 'T', ' ', 'T', ' ', 'B', ' ', 'T', ' ' },
	   { ' ', 'T', ' ', 'T', ' ', 'T', ' ', 'T' },
	   { 'T', ' ', 'T', ' ', 'T', ' ', 'T', ' ' }
	};

	checkersPos src = {'F', '2'};
	printf("Initial Board:\n");
	printBoard(board);
	printf("\n");



	SingleSourceMovesTree* tree = FindSingleSourceMove(board, &src);

	SingleSourceMovesList* listRes;
	listRes = FindSingleSourceOptimalMove(tree);
	//printList(listRes);


	//typedef struct _SingleSourceMovesTreeNode
	//{
	//	Board board;
	//	checkersPos* pos;
	//	unsigned short total_captures_so_far;
	//	struct _SingleSourceMovesTreeNode* next_move[2];

	//}SingleSourceMovesTreeNode;


	//printf("Board after Operations:\n");
	//printBoard(tree->source->next_move[1]->board);
	//printf("\n");
}

//void printList(SingleSourceMovesList* lst)
//{
//	SingleSourceMovesListCell* curr = lst->head;
//
//	while (curr != NULL)
//	{
//		printf("%c\n", curr->position->col);
//		printf("%c\n", curr->position->row);
//		printf("%d\n", curr->captures);
//		printf("\n");
//		curr = curr->next;
//	}
//}
//
