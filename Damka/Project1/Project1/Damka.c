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

void duplicateBoard (Board board, SingleSourceMovesTreeNode* moveNode)
{
	Board newBoard;
	int i, j;
	for (i = 0; i < BOARD_SIZE; i++)
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			newBoard[i][j] = board[i][j];
		}
	}
	moveNode->board;
}
SingleSourceMovesTree* FindSingleSourceMove(Board board, checkersPos* src)
{
	SingleSourceMovesTree treeMove;
	treeMove.source = FindSingleSourceMove(board, src, 0);


}

SingleSourceMovesTree* FindSingleSourceMoveHelper(Board board, checkersPos* src, int totalCaptures)
{
	SingleSourceMovesTreeNode* moveNode;
	checkersPos newPosition;
	int toolMovingPosition = 1;
	
	if (!checkPosValid) // àåìé ìà öøéê ëé îçùá îùç÷ ðâã îçùá
		return NULL;
	if (board[convertRow(src)][convertCol(src)] == ' ')
		return NULL;

	switch (board[convertRow(src)][convertCol(src)])
	{
	case ' ':
		return NULL;
		break;
	case 'T':
		toolMovingPosition = -1;
		break;
		case 'B':
		break;
		// now we check if we can move right or left

		//check right

	default:
		break;
	}
	moveNode = buildNewMoveNode(board, src, totalCaptures, NULL, NULL); // build first 

	// play without capture before
	// check if possible move[0]
	newPosition.col = src->col - toolMovingPosition;
	newPosition.row = src->row + toolMovingPosition;
	if (checkPosValid(&newPosition) && board[convertRow(newPosition.row)][convertRow(newPosition.col)] != ' ')
	{
		// we can't move to move[0]
		moveNode->next_move[0] == NULL;
	}
	else
	{
		// we can move to here
		// board should be redraw
		moveNode->next_move[0] = buildNewMoveNode(board, &newPosition, totalCaptures, NULL, NULL);
	}

	//// move[1]

	newPosition.col = src->col - toolMovingPosition;
	newPosition.row = src->row + toolMovingPosition;

	return moveNode;
}
SingleSourceMovesTreeNode* buildNewMoveNode(Board board, checkersPos* src, int totalCaptures, SingleSourceMovesTreeNode* singleMove0, SingleSourceMovesTreeNode* singleMove1)
{
	SingleSourceMovesTreeNode* moveNode = (SingleSourceMovesTreeNode*)malloc(sizeof(SingleSourceMovesTreeNode));
	if (moveNode == NULL)
		allocationFailure();

	duplicateBoard(board, moveNode);
	moveNode->pos = src;
	moveNode->total_captures_so_far = totalCaptures; // ìáãå÷ îä òåùéí
	moveNode->next_move[0] = singleMove0;
	moveNode->next_move[1] = singleMove1;
	return moveNode;
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
