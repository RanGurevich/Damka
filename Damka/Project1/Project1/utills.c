#include "utills.h"

bool checkValidation(Board board, checkersPos* src)
{
	return checkPosValid(src) && board[convertRow(src)][convertCol(src)] != EMPTY_SLOT;
}

bool checkPosValid(checkersPos* src)
{
	bool rowCheck = src->row >= 'A' && src->row < 'A' + BOARD_SIZE;
	bool colCheck = src->col >= '0' && src->col < '0' + BOARD_SIZE;
	return (rowCheck && colCheck);
}

int convertRow(checkersPos* src)
{
	return src->row - 'A';
}

int convertCol(checkersPos* src)
{
	return src->col - '0' ;
}

void allocationFailure() //error message and exit in case the allocation has failed
{
	printf("Sorry, Allocation failure");
	exit(1);
}

char getCharOnBoard(Board board, checkersPos *position) {
	return board[convertRow(position)][convertCol(position)];
}