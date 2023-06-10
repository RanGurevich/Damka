#include "utills.h"

bool checkValidation(Board board, checkersPos* src) // checks for valid pos and for not an empty slot
{
	return checkPosValid(src) && board[convertRow(src)][convertCol(src)] != EMPTY_SLOT;
}

bool checkPosValid(checkersPos* src) // checks that the position does not exceed the boundaries of the board
{
	bool rowCheck = src->row >= 'A' && src->row < 'A' + BOARD_SIZE;
	bool colCheck = src->col >= '0' && src->col < '0' + BOARD_SIZE;
	return (rowCheck && colCheck);
}

int convertRow(checkersPos* src) // convert row char into a number
{
	return src->row - 'A';
}

int convertCol(checkersPos* src) // convert col char into a number
{
	return src->col - '0' ;
}

char getCharOnBoard(Board board, checkersPos *position) // return the specific piece in the position
{
	return board[convertRow(position)][convertCol(position)];
}

void allocationFailure() //error message and exit in case the allocation has failed
{
	printf("Sorry, Allocation failure");
	exit(1);
}
