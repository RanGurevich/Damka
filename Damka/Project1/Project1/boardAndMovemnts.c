#include"boardAndMovements.h"
#include "structs.h"
#include "utills.h"

SingleSourceMovesTree* FindSingleSourceMove(Board board, checkersPos* src)
{
	SingleSourceMovesTree* treeMove = malloc(sizeof(SingleSourceMovesTree));
	if (!treeMove) {
		allocationFailure();
	}
	treeMove->source = FindSingleSourceMoveHelper(board, src, 0);
	return treeMove;
}

/*FindSingleSourceMoveHelper function is responsible for finding possible moves for a single checkers piece on the board
and returning a tree node containing the move options*/
SingleSourceMovesTreeNode* FindSingleSourceMoveHelper(Board board, checkersPos* src, int totalCaptures)
{
	SingleSourceMovesTreeNode* moveNode;
	checkersPos* newPositionRight = NULL, * newPositionLeft = NULL, * captureMovingPositionRight = NULL, * captureMovingPositionLeft = NULL;

	char currentPlayer = getCharOnBoard(board, src), opponentPlayer;
	int toolMovingPosition = 1;

	allocationsPosAndCap(&newPositionRight, &newPositionLeft, &captureMovingPositionRight, &captureMovingPositionLeft); //allocating the positions

	if (!checkValidation(board, src))
		return NULL;

	switch (currentPlayer)
	{
	case PLAYER_T:
		opponentPlayer = PLAYER_B;
		toolMovingPosition = -1;
		break;
	case PLAYER_B:
		opponentPlayer = PLAYER_T;

		break;// now we check if we can move right or left //check right
	default:
		break;
	}
	moveNode = buildNewMoveNode(board, src, totalCaptures, NULL, NULL);

	setPosAndCap(src, newPositionRight, newPositionLeft, captureMovingPositionRight, captureMovingPositionLeft, toolMovingPosition);

	movePlayerLeft(board, moveNode, src, captureMovingPositionLeft, newPositionLeft, opponentPlayer, totalCaptures);
	movePlayerRight(board, moveNode, src, captureMovingPositionRight, newPositionRight, opponentPlayer, totalCaptures);

	return moveNode;
}

void allocationsPosAndCap(checkersPos** newPositionRight, checkersPos** newPositionLeft, checkersPos** captureMovingPositionRight, checkersPos** captureMovingPositionLeft)
{
	*newPositionRight = (checkersPos*)malloc(sizeof(checkersPos));
	if (!*newPositionRight)
		allocationFailure();

	*newPositionLeft = (checkersPos*)malloc(sizeof(checkersPos));
	if (!*newPositionLeft)
		allocationFailure();

	*captureMovingPositionRight = (checkersPos*)malloc(sizeof(checkersPos));
	if (!*captureMovingPositionRight)
		allocationFailure();

	*captureMovingPositionLeft = (checkersPos*)malloc(sizeof(checkersPos));
	if (!*captureMovingPositionLeft)
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
	SingleSourceMovesTreeNode* leftMove;
	if (checkPosValid(captureMovingPositionLeft) && getCharOnBoard(board, captureMovingPositionLeft) == EMPTY_SLOT && getCharOnBoard(board, newPositionLeft) == opponentPlayer) {
		// do capture
		leftMove = captureMove(moveNode, newPositionLeft, captureMovingPositionLeft, src, board, totalCaptures, LEFT);
		moveNode->next_move[LEFT] = FindSingleSourceMoveHelper(leftMove->board, leftMove->pos, leftMove->total_captures_so_far);
	}
	else {
		regularMove(moveNode, newPositionLeft, src, board, totalCaptures, LEFT);
		free(captureMovingPositionLeft);
	}

}

void movePlayerRight(Board board, SingleSourceMovesTreeNode* moveNode, checkersPos* src, checkersPos* captureMovingPositionRight, checkersPos* newPositionRight, char opponentPlayer, int totalCaptures)
{
	SingleSourceMovesTreeNode* rightMove;
	if (checkPosValid(captureMovingPositionRight) && getCharOnBoard(board, captureMovingPositionRight) == EMPTY_SLOT && getCharOnBoard(board, newPositionRight) == opponentPlayer) {
		// do capture
		rightMove = captureMove(moveNode, newPositionRight, captureMovingPositionRight, src, board, totalCaptures, RIGHT);
		moveNode->next_move[RIGHT] = FindSingleSourceMoveHelper(rightMove->board, rightMove->pos, rightMove->total_captures_so_far);
	}
	else {
		regularMove(moveNode, newPositionRight, src, board, totalCaptures, RIGHT);
		free(captureMovingPositionRight);
	}

}

void regularMove(SingleSourceMovesTreeNode* moveNode, checkersPos* newPosition, checkersPos* src, Board board, int totalCaptures, int playOptionIndex)
{
	SingleSourceMovesTreeNode* movementToAdd = buildNewMoveNode(moveNode->board, newPosition, totalCaptures, NULL, NULL);
	moveNode->next_move[playOptionIndex] = NULL;

	if (checkPosValid(newPosition) && board[convertRow(newPosition)][convertCol(newPosition)] == EMPTY_SLOT && totalCaptures == 0)
	{
		// we can move to here
		movementToAdd->pos = newPosition;
		duplicateBoard(board, movementToAdd);
		updateBoard(movementToAdd->board, newPosition, src, NULL, movementToAdd);
		moveNode->next_move[playOptionIndex] = movementToAdd;
	}
}

SingleSourceMovesTreeNode* captureMove(SingleSourceMovesTreeNode* moveNode, checkersPos* capturedPlayer, checkersPos* capturePos, checkersPos* src, Board board, int totalCaptures, int playOptionIndex)
{
	SingleSourceMovesTreeNode* movementToAdd = buildNewMoveNode(moveNode->board, capturePos, totalCaptures + 1, NULL, NULL);
	movementToAdd->pos = capturePos;
	duplicateBoard(moveNode->board, movementToAdd); //duplicateBoard(moveNode->board, movementToAdd->board);
	updateBoard(movementToAdd->board, capturePos, src, capturedPlayer, movementToAdd);
	moveNode->next_move[playOptionIndex] = movementToAdd; /////////////////////////////////////////////////////////////////check with run this was in remark but this it should be there


	///*printf("POS: %d\n", playOptionIndex);
	printBoard(movementToAdd->board);
	//printf("XXXXX");*/


	free(capturedPlayer);
	return movementToAdd;
}

SingleSourceMovesTreeNode* buildNewMoveNode(Board board, checkersPos* src, int totalCaptures, SingleSourceMovesTreeNode* leftNode, SingleSourceMovesTreeNode* rightNode)
{
	SingleSourceMovesTreeNode* moveNode = (SingleSourceMovesTreeNode*)malloc(sizeof(SingleSourceMovesTreeNode));
	if (moveNode == NULL)
		allocationFailure();

	duplicateBoard(board, moveNode);
	moveNode->pos = src;
	moveNode->total_captures_so_far = totalCaptures; 
	moveNode->next_move[LEFT] = leftNode;
	moveNode->next_move[RIGHT] = rightNode;
	return moveNode;
}

void updateBoard(Board board, checkersPos* newPos, checkersPos* currPos, checkersPos* capturedPos, SingleSourceMovesTreeNode* moveNode)
{
	// need to remove movenode not in use
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
	printf(" +-+-+-+-+-+-+-+-+-+\n");
	printf(" + |1|2|3|4|5|6|7|8|\n");
	printf(" +-+-+-+-+-+-+-+-+-+\n");
	for (int row = 0; row < BOARD_SIZE; row++)
	{
		printf(" |%c|", 'A' + row);
		for (int col = 0; col < BOARD_SIZE; col++)
		{
			printf("%c|", board[row][col]);
		}
		printf("\n");
		printf(" +-+-+-+-+-+-+-+-+-+\n");
	}
}


/*printf("col: %c\n", moveNode->pos->col);
printf("row:%c\n", moveNode->pos->row);
printf("\n capture: %d\n", moveNode->total_captures_so_far);*/


//("col: %c\n", moveNode->pos->col);
//printf("row:%c\n", moveNode->pos->row);
//printf("\n capture: %d\n", moveNode->total_captures_so_far);

//printf("POS: %d\n", playOptionIndex);
		//printBoard(movementToAdd->board);
		//printf("XXXXX");


//void captureMove (SingleSourceMovesTreeNode* moveNode, checkersPos *capturedPlayer, checkersPos *capturePos, checkersPos* src, Board board, int totalCaptures, int playOptionIndex) {
//	SingleSourceMovesTreeNode* movementToAdd = buildNewMoveNode(moveNode->board, capturePos, totalCaptures+1, NULL, NULL);
//	movementToAdd->pos = capturePos;
//	duplicateBoard(board, movementToAdd);
//	updateBoard(movementToAdd->board, capturePos, src, capturedPlayer, movementToAdd);
//	moveNode->next_move[playOptionIndex] = movementToAdd;
//	printf("POS: %d\n", playOptionIndex);
//	printBoard(moveNode->next_move[playOptionIndex]->board);
//	printf("XXXXX");
//	free(capturedPlayer);
//}

//moveNode->next_move[playOptionIndex] = movementToAdd;
	//printf("POS: %d\n", playOptionIndex);
	//printBoard(movementToAdd->board);
	//printf("XXXXX");

//	allocationsPosAndCap(newPositionRight, newPositionLeft, captureMovingPositionRight, captureMovingPositionLeft);
	/*newPositionRight = (checkersPos*)malloc(sizeof(checkersPos));
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
		allocationFailure();*/


//void printBoard(Board board)
//{
//	printf("   0 1 2 3 4 5 6 7\n");
//	printf("  -----------------\n");
//	for (int row = 0; row < BOARD_SIZE; row++)
//	{
//		printf("%d |", row);
//		for (int col = 0; col < BOARD_SIZE; col++)
//		{
//			printf("%c|", board[row][col]);
//		}
//		printf("\n");
//		printf("  -----------------\n");
//	}
//}
