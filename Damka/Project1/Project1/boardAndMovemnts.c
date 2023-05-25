#include"boardAndMovements.h"
#include "structs.h"
#include "utills.h"

void allocationsPosAndCap(checkersPos* newPositionRight, checkersPos* newPositionLeft, checkersPos* captureMovingPositionRight, checkersPos* captureMovingPositionLeft);
void setPosAndCap(checkersPos* src, checkersPos* newPositionRight, checkersPos* newPositionLeft, checkersPos* captureMovingPositionRight, checkersPos* captureMovingPositionLeft, int toolMovingPosition);
void movePlayerLeft(Board board, SingleSourceMovesTreeNode* moveNode, checkersPos* src, checkersPos* captureMovingPositionLeft, checkersPos* newPositionLeft, char opponentPlayer, int totalCaptures);
void movePlayerRight(Board board, SingleSourceMovesTreeNode* moveNode, checkersPos* src, checkersPos* captureMovingPositionLeft, checkersPos* newPositionLeft, char opponentPlayer, int totalCaptures);
bool checkPosValid(checkersPos* src);
void allocationFailure();
void duplicateBoard(Board board, SingleSourceMovesTreeNode* moveNode);
void regularMove(SingleSourceMovesTreeNode* moveNode, checkersPos* newPosition, checkersPos* src, Board board, int totalCaptures, int playOptionIndex);
void printBoard(Board board);




SingleSourceMovesTree* FindSingleSourceMove(Board board, checkersPos* src)
{
	SingleSourceMovesTree *treeMove = malloc(sizeof(SingleSourceMovesTree));
	if (!treeMove) {
		allocationFailure();
	}
	treeMove->source = FindSingleSourceMoveHelper(board, src, 0);
	return treeMove;
}



SingleSourceMovesTreeNode* FindSingleSourceMoveHelper(Board board, checkersPos* src, int totalCaptures)
{
	SingleSourceMovesTreeNode* moveNode;
	checkersPos* newPositionRight = NULL, * newPositionLeft = NULL, * captureMovingPositionRight = NULL, * captureMovingPositionLeft = NULL;

	char currentPlayer = getCharOnBoard(board, src), opponentPlayer;
//	char opponentPlayer = currentPlayer == PLAYER_T ? PLAYER_B : PLAYER_T;
	int toolMovingPosition = 1;

//	allocationsPosAndCap(newPositionRight, newPositionLeft, captureMovingPositionRight, captureMovingPositionLeft);
	newPositionRight = (checkersPos*)malloc(sizeof(checkersPos));
	if (!newPositionRight)
		allocationFailure();

	newPositionLeft = (checkersPos*)malloc(sizeof(checkersPos));
	if (!newPositionLeft)
		allocationFailure();

	captureMovingPositionRight = (checkersPos*)malloc(sizeof(checkersPos));
	if (!captureMovingPositionRight)
		allocationFailure();

	captureMovingPositionLeft = (checkersPos*)malloc(sizeof(checkersPos));
	if (!captureMovingPositionLeft)
		allocationFailure();

	if (!checkValidation(board, src))
		return NULL;

	switch (currentPlayer)
	{
	case PLAYER_T:
		opponentPlayer = PLAYER_B;
		break;
	case PLAYER_B:
		opponentPlayer = PLAYER_T;
		toolMovingPosition = -1;

		break;// now we check if we can move right or left //check right
	default:
		break;
	}
	moveNode = buildNewMoveNode(board, src, totalCaptures, NULL, NULL); // build first 	// play without capture before	// check if possible move[0]
// 
	//do move position to right and the left


	setPosAndCap(src, newPositionRight, newPositionLeft, captureMovingPositionRight, captureMovingPositionLeft, toolMovingPosition);
	
	movePlayerLeft(board, moveNode, src, captureMovingPositionLeft, newPositionLeft , opponentPlayer, totalCaptures);
	movePlayerRight(board, moveNode, src, captureMovingPositionRight, newPositionRight, opponentPlayer, totalCaptures);

	return moveNode;
}

void allocationsPosAndCap(checkersPos* newPositionRight, checkersPos* newPositionLeft, checkersPos* captureMovingPositionRight, checkersPos* captureMovingPositionLeft)
{
	newPositionRight = (checkersPos*)malloc(sizeof(checkersPos));
	if (!newPositionRight)
		allocationFailure();

	newPositionLeft = (checkersPos*)malloc(sizeof(checkersPos));
	if (!newPositionLeft)
		allocationFailure();

	captureMovingPositionRight = (checkersPos*)malloc(sizeof(checkersPos));
	if (!captureMovingPositionRight)
		allocationFailure();

	captureMovingPositionLeft = (checkersPos*)malloc(sizeof(checkersPos));
	if (!captureMovingPositionLeft)
		allocationFailure();
}

void setPosAndCap(checkersPos* src, checkersPos* newPositionRight, checkersPos* newPositionLeft, checkersPos* captureMovingPositionRight, checkersPos* captureMovingPositionLeft, int toolMovingPosition)
{
	newPositionRight->row = src->row - toolMovingPosition;
	newPositionRight->col = src->col + 1;
	newPositionLeft->row = src->row - toolMovingPosition;
	newPositionLeft->col = src->col - 1;
	captureMovingPositionRight->row = newPositionRight->row - toolMovingPosition;
	captureMovingPositionRight->col = newPositionRight->col + 1;
	captureMovingPositionLeft->row = newPositionLeft->row - toolMovingPosition;
	captureMovingPositionLeft->col = newPositionLeft->col - 1;
}

void movePlayerLeft(Board board, SingleSourceMovesTreeNode* moveNode, checkersPos* src, checkersPos* captureMovingPositionLeft, checkersPos* newPositionLeft, char opponentPlayer, int totalCaptures)
{
	if (checkPosValid(captureMovingPositionLeft) && getCharOnBoard(board, captureMovingPositionLeft) == EMPTY_SLOT && getCharOnBoard(board, newPositionLeft) == opponentPlayer) {
		// do capture
		captureMove(moveNode, newPositionLeft, captureMovingPositionLeft, src, board, totalCaptures, LEFT);
		moveNode->next_move[LEFT]->next_move[LEFT] = FindSingleSourceMoveHelper(moveNode->next_move[LEFT]->board, moveNode->next_move[LEFT]->pos, moveNode->next_move[LEFT]->total_captures_so_far);
	}
	else {
		regularMove(moveNode, newPositionLeft, src, board, totalCaptures, LEFT);
		free(captureMovingPositionLeft);
	}
}

void movePlayerRight(Board board, SingleSourceMovesTreeNode* moveNode, checkersPos* src, checkersPos* captureMovingPositionRight, checkersPos* newPositionRight, char opponentPlayer, int totalCaptures)
{
	if (checkPosValid(captureMovingPositionRight) && getCharOnBoard(board, captureMovingPositionRight) == EMPTY_SLOT && getCharOnBoard(board, newPositionRight) == opponentPlayer) {
		// do capture
		captureMove(moveNode, newPositionRight, captureMovingPositionRight, src, board, totalCaptures, RIGHT);
		moveNode->next_move[RIGHT]->next_move[RIGHT] = FindSingleSourceMoveHelper(moveNode->next_move[RIGHT]->board, moveNode->next_move[RIGHT]->pos, moveNode->next_move[RIGHT]->total_captures_so_far);
	}
	else {
		regularMove(moveNode, newPositionRight, src, board, totalCaptures, RIGHT);
		free(captureMovingPositionRight);
	}
}

void regularMove(SingleSourceMovesTreeNode *moveNode, checkersPos *newPosition, checkersPos* src, Board board, int totalCaptures, int playOptionIndex) {
	SingleSourceMovesTreeNode* movementToAdd = buildNewMoveNode(moveNode->board, newPosition, totalCaptures, NULL, NULL);
	moveNode->next_move[playOptionIndex] = NULL;

	if (checkPosValid(newPosition) && board[convertRow(newPosition)][convertCol(newPosition)] == EMPTY_SLOT && totalCaptures == 0)
	{
		// we can move to here
		movementToAdd->pos = newPosition;
		duplicateBoard(board, movementToAdd);
		updateBoard(movementToAdd->board, newPosition, src, NULL, movementToAdd);
		printf("XXXXX");
		printBoard(movementToAdd->board);
		printf("XXXXX");
		moveNode->next_move[playOptionIndex] = movementToAdd;
	}
}

void captureMove (SingleSourceMovesTreeNode* moveNode, checkersPos *capturedPlayer, checkersPos *capturePos, checkersPos* src, Board board, int totalCaptures, int playOptionIndex) {
	SingleSourceMovesTreeNode* movementToAdd = buildNewMoveNode(moveNode->board, capturePos, totalCaptures+1, NULL, NULL);
	movementToAdd->pos = capturePos;
	duplicateBoard(board, movementToAdd);
	updateBoard(moveNode->board, capturePos, src, capturedPlayer, movementToAdd);
	moveNode->next_move[playOptionIndex] = movementToAdd;
	free(capturedPlayer);
}

SingleSourceMovesTreeNode* buildNewMoveNode(Board board, checkersPos* src, int totalCaptures, SingleSourceMovesTreeNode* leftNode, SingleSourceMovesTreeNode* rightNode)
{
	SingleSourceMovesTreeNode* moveNode = (SingleSourceMovesTreeNode*)malloc(sizeof(SingleSourceMovesTreeNode));
	if (moveNode == NULL)
		allocationFailure();

	duplicateBoard(board, moveNode);
	moveNode->pos = src;
	moveNode->total_captures_so_far = totalCaptures; // ìáãå÷ îä òåùéí
	moveNode->next_move[LEFT] = leftNode;
	moveNode->next_move[RIGHT] = rightNode;
	return moveNode;
}

void updateBoard(Board board, checkersPos* newPos, checkersPos* currPos, checkersPos* capturedPos, SingleSourceMovesTreeNode* moveNode) {
	char playerToMove = board[convertRow(currPos)][convertCol(currPos)];
	board[convertRow(currPos)][convertCol(currPos)] = EMPTY_SLOT;
	if (capturedPos) {
		board[convertRow(capturedPos)][convertCol(capturedPos)] = EMPTY_SLOT;
	}
	board[convertRow(newPos)][convertCol(newPos)] = playerToMove;
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

void printBoard(Board board)
{
	printf("   0 1 2 3 4 5 6 7\n");
	printf("  -----------------\n");
	for (int row = 0; row < BOARD_SIZE; row++)
	{
		printf("%d |", row);
		for (int col = 0; col < BOARD_SIZE; col++)
		{
			printf("%c|", board[row][col]);
		}
		printf("\n");
		printf("  -----------------\n");
	}
}
