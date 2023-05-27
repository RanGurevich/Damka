#pragma once
#include "utills.h"

void insertDataToEndListSingleSource(SingleSourceMovesList* lst, checkersPos* position, unsigned short captures, SingleSourceMovesListCell* next);
void insertNodeToEndListSingleSource(SingleSourceMovesList* lst, SingleSourceMovesListCell* tail);
void makeEmptyListSingleSource(SingleSourceMovesList* lst);
bool isEmptyListSingleSource(SingleSourceMovesList* lst);
SingleSourceMovesListCell* createNewListNodeSingleSource(checkersPos* position, unsigned short captures, SingleSourceMovesListCell* next);
