#include "structs.h"

bool checkPosValid(checkersPos* src);
void allocationFailure();
void duplicateBoard(Board board, SingleSourceMovesTreeNode* moveNode);
void regularMovePlayOption(SingleSourceMovesTreeNode* moveNode, checkersPos newPosition, checkersPos* src, Board board, int totalCaptures, int playOptionIndex);

SingleSourceMovesTree* FindSingleSourceMove(Board board, checkersPos* src)
{
	SingleSourceMovesTree *treeMove = malloc(sizeof(SingleSourceMovesTree));
	if (!treeMove) {
		allocationFailure();
	}
	treeMove->source = FindSingleSourceMoveHelper(board, src, 0);
	return treeMove;
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
	regularMovePlayOption(moveNode, newPosition, src, board, totalCaptures, 0);

	//// move[1]

	newPosition.col = src->col + toolMovingPosition;
	newPosition.row = src->row - toolMovingPosition;
	regularMovePlayOption(moveNode, newPosition, src, board, totalCaptures, 1);
	return moveNode;
}

void regularMovePlayOption(SingleSourceMovesTreeNode * moveNode, checkersPos newPosition, checkersPos* src, Board board, int totalCaptures, int playOptionIndex) {
	if (checkPosValid(&newPosition) && board[convertRow(newPosition.row)][convertRow(newPosition.col)] != EMPTY_SLOT)
	{
		// we can move to here
		moveNode->pos = &newPosition;
		duplicateBoard(board, moveNode);
		updateBoard(moveNode->board, &newPosition, src, NULL, moveNode);
		moveNode->next_move[0] = buildNewMoveNode(moveNode->board, &newPosition, totalCaptures, NULL, NULL);
		moveNode->next_move[1] = buildNewMoveNode(moveNode->board, &newPosition, totalCaptures, NULL, NULL);
	}
	else
	{
		// we can't move to move[playOptionIndex]
		moveNode->next_move[playOptionIndex] = NULL;
	}
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

void duplicateBoard(Board board, SingleSourceMovesTreeNode* moveNode)
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



