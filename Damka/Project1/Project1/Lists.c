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

MultipleSourceMovesListCell* createNewListNodeAllOptions(SingleSourceMovesList* characterOptionPlayList, MultipleSourceMovesListCell* next)
{
	MultipleSourceMovesListCell* res;
	res = (MultipleSourceMovesListCell*)malloc(sizeof(MultipleSourceMovesListCell));
	if (!res)
		allocationFailure();
	//res->single_source_moves_list = (SingleSourceMovesList*)(malloc(sizeof())) // if we need to allocate
	res->single_source_moves_list = characterOptionPlayList;
	res->next = next;
	return res;
}

void insertDataToEndListAllOptions(MultipleSourceMovesList* lst, SingleSourceMovesList* characterOptionPlayList, MultipleSourceMovesListCell* next)
{
	MultipleSourceMovesListCell* newTail;
	newTail = createNewListNodeAllOptions(characterOptionPlayList, next);
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