#pragma once
#include "structs.h"

bool checkPosValid(checkersPos* src);
int convertRow(checkersPos* src);
int convertCol(checkersPos* src);
char getCharOnBoard(Board board, checkersPos* position);