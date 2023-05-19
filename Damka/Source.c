#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define BOARD_SIZE 8

typedef struct checkerPos
{
	char row, col;
}checkersPos;

typedef unsigned char Board[BOARD_SIZE][BOARD_SIZE];

typedef unsigned char Player;

typedef struct _SingleSourceMovesTreeNode
{
	Board board;
	checkersPos* pos;
	unsigned short total_captures_so_far;
	struct _SingleSourceMovesTreeNode* next_move[2];

}SingleSourceMovesTreeNode;

typedef struct _SingleSourceMovesTree {
	SingleSourceMovesTreeNode* source;
}SingleSourceMovesTree;

SingleSourceMovesTree* FindSingleSourceMove(Board board, checkersPos* src);


void main()
{

}

SingleSourceMovesTree* FindSingleSourceMove(Board board, checkersPos* src)
{
	SingleSourceMovesTree treeMove;
	treeMove.source = FindSingleSourceMove(board, src, 0);


}

SingleSourceMovesTree* FindSingleSourceMoveHelper(Board board, checkersPos* src)
{
	if (checkPosValid == false)
		return NULL;
	if (board[convertRow(src)][convertCol(src)] == ' ')
		return NULL;

	SingleSourceMovesTreeNode* moveNode = (SingleSourceMovesTreeNode*)malloc(sizeof(SingleSourceMovesTreeNode));
	if (moveNode == NULL)
		allocationFailure();

	moveNode->board = board;
	moveNode->pos = src;
	moveNode->total_captures_so_far; // לבדוק מה עושים
	moveNode->next_move[0] = NULL;
	moveNode->next_move[1] = NULL;



}

bool checkPosValid(checkersPos* src)
{
	return src->row < 'A' || src->row >= 'A' + BOARD_SIZE || src->col < '1' || src->col >= '1' + BOARD_SIZE;
}

int convertRow(checkersPos* src)
{
	return src->row - 'A' + 1;
}

int convertCol(checkersPos* src)
{
	return src->col - '0';
}


void allocationFailure() //error message and exit in case the allocation has failed
{
	printf("Sorry, Allocation failure");
	exit(1);
}