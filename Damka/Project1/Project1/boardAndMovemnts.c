#include"boardAndMovements.h"
#include "structs.h"
#include "utills.h"

/*FindSingleSourceMove function is responsible for finding possible moves for a single checkers tool on the board
and returning a tree of options move*/
SingleSourceMovesTree* FindSingleSourceMove(Board board, checkersPos* src)
{
	SingleSourceMovesTree* treeMove = malloc(sizeof(SingleSourceMovesTree));
	if (!treeMove) {
		allocationFailure();
	}
	treeMove->source = FindSingleSourceMoveHelper(board, src, 0); // calling for helper
	return treeMove;
}

SingleSourceMovesTreeNode* FindSingleSourceMoveHelper(Board board, checkersPos* src, int totalCaptures) // helper function for FindSingleSourceMove
{
	SingleSourceMovesTreeNode* moveNode;
	checkersPos* newPositionRight = NULL, * newPositionLeft = NULL, * captureMovingPositionRight = NULL, * captureMovingPositionLeft = NULL;

	char currentPlayer = getCharOnBoard(board, src), opponentPlayer;
	int toolMovingPosition = 1;

	allocationsPosAndCap(&newPositionRight, &newPositionLeft, &captureMovingPositionRight, &captureMovingPositionLeft); //allocating the positions

	if (!checkValidation(board, src))
		return NULL;

	switch (currentPlayer) // checking for a specific checkers piece
	{
	case PLAYER_T:
		opponentPlayer = PLAYER_B;
		toolMovingPosition = -1;
		break;
	case PLAYER_B:
		opponentPlayer = PLAYER_T;

		break;
	default:
		break;
	}
	moveNode = buildNewMoveNode(board, src, totalCaptures, NULL, NULL);

	setPosAndCap(src, newPositionRight, newPositionLeft, captureMovingPositionRight, captureMovingPositionLeft, toolMovingPosition); // setting postions and possible captures

	movePlayerLeft(board, moveNode, src, captureMovingPositionLeft, newPositionLeft, opponentPlayer, totalCaptures); // recursive calls for moving the pieace right or left
	movePlayerRight(board, moveNode, src, captureMovingPositionRight, newPositionRight, opponentPlayer, totalCaptures);

	return moveNode;
}

/* allocate memory for new positions and capture positions*/
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

/*set positions and captures based on the source position and tool moving position*/
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

/* movePlayerLeft creates a new TreeNode if there is a possible move or capture to the left */
void movePlayerLeft(Board board, SingleSourceMovesTreeNode* moveNode, checkersPos* src, checkersPos* captureMovingPositionLeft, checkersPos* newPositionLeft, char opponentPlayer, int totalCaptures)
{
	SingleSourceMovesTreeNode* leftMove;

	if (checkPosValid(captureMovingPositionLeft) && getCharOnBoard(board, captureMovingPositionLeft) == EMPTY_SLOT && getCharOnBoard(board, newPositionLeft) == opponentPlayer) // check if a capture move is possible
	{
		leftMove = captureMove(moveNode, newPositionLeft, captureMovingPositionLeft, src, board, totalCaptures, LEFT); // creates a new move TreeNode for the captured move
		moveNode->next_move[LEFT] = FindSingleSourceMoveHelper(leftMove->board, leftMove->pos, leftMove->total_captures_so_far); // assign the captured node in the correct position and call for the recursive function
	}
	else  
	{
		regularMove(moveNode, newPositionLeft, src, board, totalCaptures, LEFT); // if three is no way for capture assign and create a regular TreeNode
		free(captureMovingPositionLeft);
	}
}

/* movePlayerLeft creates a new TreeNode if there is a possible move or capture to the right */
void movePlayerRight(Board board, SingleSourceMovesTreeNode* moveNode, checkersPos* src, checkersPos* captureMovingPositionRight, checkersPos* newPositionRight, char opponentPlayer, int totalCaptures)
{
	SingleSourceMovesTreeNode* rightMove;
	if (checkPosValid(captureMovingPositionRight) && getCharOnBoard(board, captureMovingPositionRight) == EMPTY_SLOT && getCharOnBoard(board, newPositionRight) == opponentPlayer) // check if a capture move is possible
	{
		// do capture
		rightMove = captureMove(moveNode, newPositionRight, captureMovingPositionRight, src, board, totalCaptures, RIGHT); // creates a new move TreeNode for the captured move
		moveNode->next_move[RIGHT] = FindSingleSourceMoveHelper(rightMove->board, rightMove->pos, rightMove->total_captures_so_far); // assign the captured node in the correct position and call for the recursive function
	}
	else 
	{
		regularMove(moveNode, newPositionRight, src, board, totalCaptures, RIGHT); // if three is no way for capture assign and create a regular TreeNode
		free(captureMovingPositionRight);
	}
}

/*regularMove function create and assign a regular TreeNode */
void regularMove(SingleSourceMovesTreeNode* moveNode, checkersPos* newPosition, checkersPos* src, Board board, int totalCaptures, int playOptionIndex)
{
	SingleSourceMovesTreeNode* movementToAdd = buildNewMoveNode(moveNode->board, newPosition, totalCaptures, NULL, NULL);
	moveNode->next_move[playOptionIndex] = NULL;

	if (checkPosValid(newPosition) && board[convertRow(newPosition)][convertCol(newPosition)] == EMPTY_SLOT && totalCaptures == 0) //checks for valid position
	{
		movementToAdd->pos = newPosition;
		duplicateBoard(board, movementToAdd);
		updateBoard(movementToAdd->board, newPosition, src, NULL);
		moveNode->next_move[playOptionIndex] = movementToAdd;
	}
	else
	{
		free(movementToAdd); 
		free(newPosition); 
	}
}

/*captureMove function create and assign a captureMove TreeNode */
SingleSourceMovesTreeNode* captureMove(SingleSourceMovesTreeNode* moveNode, checkersPos* capturedPlayer, checkersPos* capturePos, checkersPos* src, Board board, int totalCaptures, int playOptionIndex)
{
	SingleSourceMovesTreeNode* movementToAdd = buildNewMoveNode(moveNode->board, capturePos, totalCaptures + 1, NULL, NULL);
	movementToAdd->pos = capturePos;
	duplicateBoard(moveNode->board, movementToAdd); //duplicateBoard(moveNode->board, movementToAdd->board);
	updateBoard(movementToAdd->board, capturePos, src, capturedPlayer);

	//moveNode->next_move[playOptionIndex] = movementToAdd; /////////////////////////////////////////////////////////////////check with run this was in remark but this it should be there

	///*printf("POS: %d\n", playOptionIndex);
	//printBoard(movementToAdd->board);
	//printf("XXXXX");*/

	free(capturedPlayer);
	return movementToAdd;
}

/* buildNewMoveNode functions creates a nre TreeNode with a given parameters*/
SingleSourceMovesTreeNode* buildNewMoveNode(Board board, checkersPos* src, int totalCaptures, SingleSourceMovesTreeNode* leftNode, SingleSourceMovesTreeNode* rightNode)
{
	SingleSourceMovesTreeNode* moveNode = (SingleSourceMovesTreeNode*)malloc(sizeof(SingleSourceMovesTreeNode));
	if (moveNode == NULL)
		allocationFailure();

	duplicateBoard(board, moveNode); // updating the board for each TreeNode
	moveNode->pos = src;
	moveNode->total_captures_so_far = totalCaptures; 
	moveNode->next_move[LEFT] = leftNode;
	moveNode->next_move[RIGHT] = rightNode;

	return moveNode;
}

void updateBoard(Board board, checkersPos* newPos, checkersPos* currPos, checkersPos* capturedPos) // Update the board after a move is made
{
	char playerToMove = board[convertRow(currPos)][convertCol(currPos)];
	board[convertRow(currPos)][convertCol(currPos)] = EMPTY_SLOT;
	if (capturedPos) {
		board[convertRow(capturedPos)][convertCol(capturedPos)] = EMPTY_SLOT;
	}
	board[convertRow(newPos)][convertCol(newPos)] = playerToMove;
}

void duplicateBoard(Board board, SingleSourceMovesTreeNode* moveNode) //creates a duplication of the board
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