#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define BOARD_SIZE 8
#define EMPTY_SLOT ' '
#define PLAYER_1_CHAR 'T'
#define PLAYER_2_CHAR 'B'

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
	int i, j;

	for (i = 0; i < BOARD_SIZE; i++)
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			moveNode->board[i][j] = board[i][j];
		}
	}
}

SingleSourceMovesTree* FindSingleSourceMove(Board board, checkersPos* src)
{
	SingleSourceMovesTree treeMove;
	treeMove.source = FindSingleSourceMoveHelper(board, src, 0);
}

void updateBoard(Board board, checkersPos* toMovePoint, checkersPos* toRemove1, checkersPos* toRemove2, SingleSourceMovesTreeNode* moveNode) {
	char playerToMove = board[convertRow(toRemove1)][convertCol(toRemove1)];
	board[convertRow(toRemove1)][convertCol(toRemove1)] = EMPTY_SLOT;
	if (toRemove2) {
		board[convertRow(toRemove1)][convertCol(toRemove2)] = EMPTY_SLOT;
	}
	board[convertRow(toMovePoint)][convertCol(toMovePoint)] = playerToMove;
}

SingleSourceMovesTree* FindSingleSourceMoveHelper(Board board, checkersPos* src, int totalCaptures)
{
	SingleSourceMovesTreeNode* moveNode;
	checkersPos newPosition;
	int toolMovingPosition = 1;
	
	if (!checkPosValid(src)) // we check if the movement is legal
		return NULL;
	if (board[convertRow(src)][convertCol(src)] == EMPTY_SLOT)
		return NULL;

	switch (board[convertRow(src)][convertCol(src)])
	{
	case EMPTY_SLOT:
		return NULL;
		break;
	case PLAYER_1_CHAR:
		toolMovingPosition = -1;
		break;
		case PLAYER_2_CHAR:
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
	if (checkPosValid(&newPosition) && board[convertRow(newPosition.row)][convertRow(newPosition.col)] != EMPTY_SLOT)
	{
		// we can move to here
		moveNode->pos = &newPosition;
		duplicateBoard(board, moveNode);
		updateBoard(moveNode->board, &newPosition, src, NULL, moveNode);
		moveNode->next_move[0] = buildNewMoveNode(moveNode->board, &newPosition, totalCaptures, NULL, NULL);
	}
	else
	{
		// we can't move to move[0]
		moveNode->next_move[0] == NULL;
	}

	//// move[1]

	newPosition.col = src->col + toolMovingPosition;
	newPosition.row = src->row - toolMovingPosition;
	if (checkPosValid(&newPosition) && board[convertRow(newPosition.row)][convertRow(newPosition.col)] != EMPTY_SLOT)
	{
		// we can't move to move[]
		moveNode->next_move[1] == NULL;
	}
	else
	{
		// we can move to here
		// board should be redraw
		moveNode->next_move[1] = buildNewMoveNode(board, &newPosition, totalCaptures, NULL, NULL);
	}
	// need to do the captures here
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
