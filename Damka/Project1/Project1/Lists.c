#pragma once
#include "Lists.h"
#include "structs.h"
#include "utills.h"

void makeEmptyListSingleSource(SingleSourceMovesList* lst)
{
	lst->head = NULL;
	lst->tail = NULL;
}

bool isEmptyListSingleSource(SingleSourceMovesList* lst)
{
	if (lst->head == NULL)
		return true;
	else
		return false;
}

SingleSourceMovesListCell* createNewListNodeSingleSource(checkersPos* position, unsigned short captures, SingleSourceMovesListCell* next)
{
	SingleSourceMovesListCell* res;
	res = (SingleSourceMovesListCell*)malloc(sizeof(SingleSourceMovesListCell));
	if (!res)
		allocationFailure();
	res->position = position;
	res->next = next;
	res->captures = captures;
	return res;
}

void insertDataToEndListSingleSource(SingleSourceMovesList* lst, checkersPos* position, unsigned short captures, SingleSourceMovesListCell* next)
{
	SingleSourceMovesListCell* newTail;
	newTail = createNewListNodeSingleSource(position, captures, next);
	insertNodeToEndListSingleSource(lst, newTail);
}

void insertNodeToEndListSingleSource(SingleSourceMovesList* lst, SingleSourceMovesListCell* tail)
{
	if (isEmptyListSingleSource(lst)) {
		lst->head = lst->tail = tail;
	}
	else {
		lst->tail->next = tail;
		lst->tail = tail;
	}
	tail->next = NULL;
}

void makeEmptyListAllOptions(MultipleSourceMovesList* lst)
{
	lst->head = NULL;
	lst->tail = NULL;
}

bool isEmptyListAllOptions(MultipleSourceMovesList* lst)
{
	if (lst->head == NULL)
		return true;
	else
		return false;
}

//MultipleSourceMovesListCell* createNewListNodeAllOptions(SingleSourceMovesList* characterOptionPlayList, MultipleSourceMovesListCell* next)
//{
//	MultipleSourceMovesListCell* res;
//	res = (MultipleSourceMovesListCell*)malloc(sizeof(MultipleSourceMovesListCell));
//	if (!res)
//		allocationFailure();
//	res->single_source_moves_list = (SingleSourceMovesList*)(malloc(sizeof(SingleSourceMovesList))); // if we need to allocate
//	res->single_source_moves_list = characterOptionPlayList;
//	res->next = next;
//	return res;
//}

MultipleSourceMovesListCell* createNewListNodeAllOptions(SingleSourceMovesList* characterOptionPlayList, MultipleSourceMovesListCell* next)
{
	MultipleSourceMovesListCell* res = (MultipleSourceMovesListCell*)malloc(sizeof(MultipleSourceMovesListCell));
	if (!res) {
		allocationFailure();
	}
	res->single_source_moves_list = (SingleSourceMovesList*)malloc(sizeof(SingleSourceMovesList));
	if (!res->single_source_moves_list) {
		allocationFailure();
	}
	makeEmptyListSingleSource(res->single_source_moves_list);
	SingleSourceMovesListCell* curr = characterOptionPlayList->head;
	while (curr != NULL) {
		// Create a new checkersPos instance and copy the values
		checkersPos* newPos = (checkersPos*)malloc(sizeof(checkersPos));
		if (!newPos) {
			allocationFailure();
		}
		newPos->row = curr->position->row;
		newPos->col = curr->position->col;

		// Insert the new checkersPos instance into the new list
		insertDataToEndListSingleSource(res->single_source_moves_list, newPos, curr->captures, NULL);
		curr = curr->next;
	}
	res->next = next;
	return res;
}


void insertDataToEndListAllOptions(MultipleSourceMovesList* lst, SingleSourceMovesList* characterOptionPlayList, MultipleSourceMovesListCell* next)
{
	MultipleSourceMovesListCell* newTail;
	newTail = createNewListNodeAllOptions(characterOptionPlayList, next);
	//printf("new tail all option:\n");
	//printf("pos: ", characterOptionPlayList->)
	insertNodeToEndListAllOptions(lst, newTail);
}

void insertNodeToEndListAllOptions(MultipleSourceMovesList* lst, MultipleSourceMovesListCell* tail)
{
	if (isEmptyListAllOptions(lst)) {
		lst->head = lst->tail = tail;
	}
	else {
		lst->tail->next = tail;
		lst->tail = tail;
	}
	tail->next = NULL;
}