#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "structs.h"
#include "boardAndMovements.h"
#include "movements.h"
#include "gameManegment.h"

void printList(SingleSourceMovesList* lst);
void printTreeLDR(SingleSourceMovesTree* tr);
void printTreeLDRHelper(SingleSourceMovesTreeNode* root);
void printListAllOptions(MultipleSourceMovesList* lst);


void main()
{

	Board board = {
	   { ' ', ' ', ' ', 'T', ' ', ' ', ' ', 'T' },
	   { 'T', ' ', 'T', ' ', 'T', ' ', ' ', ' ' },
	   { ' ', 'B', ' ', 'B', ' ', ' ', ' ', ' ' },
	   { ' ', ' ', ' ', ' ', ' ', ' ', 'T', ' ' },
	   { ' ', 'T', ' ', 'T', ' ', ' ', ' ', ' ' },
	   { 'B', ' ', ' ', ' ', 'T', ' ', ' ', ' ' },
	   { ' ', 'B', ' ', 'T', ' ', 'T', ' ', 'B' },
	   { 'B', ' ', 'B', ' ', 'B', ' ', 'B', ' ' }
	};

	checkersPos src = {'A', '7'};  ///H4,F2,D4,B6
	printf("Initial Board:\n");
	printBoard(board);
	printf("\n");
	


	//SingleSourceMovesTree* tree = FindSingleSourceMove(board, &src);


//	printf("\nprint in-order\n");
	//printTreeLDR(tree);

//	SingleSourceMovesList* listRes;
//	listRes = FindSingleSourceOptimalMove(tree);
//	printListAllOptions(FindAllPossiblePlayerMoves(board, 'B'));
// 	   
//	printList(listRes);


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
	Turn(board, 'T');
}

//void printList(SingleSourceMovesList* lst)
//{
//	SingleSourceMovesListCell* curr = lst->head;
//	int count = 1;
//
//	while (curr != NULL)
//	{
//		printf("num of cell: %d \n", count);
//		printf("col: %c\n", curr->position->col);
//		printf("row:%c\n", curr->position->row);
//		printf("captures: % d\n", curr->captures);
//		printf("\n");
//		count++;
//		curr = curr->next;
//	}
//}

void printListAllOptions(MultipleSourceMovesList* lst)
{
	MultipleSourceMovesListCell* curr = lst->head;
	int count = 1;

	while (curr != NULL)
	{
		printf("Multiple Source Moves number : %d \n", count);
		printList(curr->single_source_moves_list);
		curr = curr->next;
		count++;
	}
}

void printTreeLDR(SingleSourceMovesTree* tr)
{
	printTreeLDRHelper(tr->source);
	printf("\n");
}

void printTreeLDRHelper(SingleSourceMovesTreeNode* root)
{
	if (root == NULL)
		return;
	else
	{
		printTreeLDRHelper(root->next_move[LEFT]);
		printf("col: %c\n", root->pos->col);
		printf("row:%c\n", root->pos->row);
		printf("captures: % d\n", root->total_captures_so_far);
		printTreeLDRHelper(root->next_move[RIGHT]);
	}
}

