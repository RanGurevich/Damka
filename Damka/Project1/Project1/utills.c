#include "utills.h"

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