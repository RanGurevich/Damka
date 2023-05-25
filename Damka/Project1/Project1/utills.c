#include "utills.h"

bool checkValidation(Board board, checkersPos* src)
{
	return checkPosValid(src) && board[convertRow(src)][convertCol(src)] == EMPTY_SLOT;
}

bool checkPosValid(checkersPos* src)
{
	return src->row < 'A' || src->row >= 'A' + BOARD_SIZE || src->col < '1' || src->col >= '1' + BOARD_SIZE;
}

int convertRow(checkersPos* src)
{
	return src->row - 'a';
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

char getCharOnBoard(Board board, checkersPos *position) {
	return board[convertRow(position)][convertCol(position)];
}