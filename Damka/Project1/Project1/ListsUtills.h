#ifndef __LISTS_UTILLS_H
#define __LISTS_UTILLS_H

#include "Utills.h"
#include "Structs.h"

void insertDataToEndListSingleSource(SingleSourceMovesList* lst, checkersPos* position, unsigned short captures, SingleSourceMovesListCell* next);
SingleSourceMovesListCell* createNewListNodeSingleSource(checkersPos* position, unsigned short captures, SingleSourceMovesListCell* next);
void insertNodeToEndListSingleSource(SingleSourceMovesList* lst, SingleSourceMovesListCell* tail);
void makeEmptyListSingleSource(SingleSourceMovesList* lst);
bool isEmptyListSingleSource(SingleSourceMovesList* lst);
void insertDataToEndListAllOptions(MultipleSourceMovesList* lst, SingleSourceMovesList* characterOptionPlayList, MultipleSourceMovesListCell* next);
MultipleSourceMovesListCell* createNewListNodeAllOptions(SingleSourceMovesList* characterOptionPlayList, MultipleSourceMovesListCell* next);
void insertNodeToEndListAllOptions(MultipleSourceMovesList* lst, MultipleSourceMovesListCell* tail);
void makeEmptyListAllOptions(MultipleSourceMovesList* lst);
bool isEmptyListAllOptions(MultipleSourceMovesList* lst);
void freeSingleSourceMovesList(SingleSourceMovesList* list);
void freeMultipleSourceMovesList(MultipleSourceMovesList* list);


#endif