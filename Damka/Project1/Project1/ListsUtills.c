#include "ListsUtills.h"
#include "Structs.h"
#include "Utills.h"

/* inserts data into a SingleSourceMovesListCell at the end of the list */
void insertDataToEndListSingleSource(SingleSourceMovesList* lst, checkersPos* position, unsigned short captures, SingleSourceMovesListCell* next)
{
	SingleSourceMovesListCell* newTail;
	newTail = createNewListNodeSingleSource(position, captures, next);
	insertNodeToEndListSingleSource(lst, newTail);
}

/* creates a new SingleSourceMovesListCell with given parameters */
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

void insertNodeToEndListSingleSource(SingleSourceMovesList* lst, SingleSourceMovesListCell* tail) // insert the SingleSourceMovesListCell at the end of the list
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

void makeEmptyListSingleSource(SingleSourceMovesList* lst) // initializes SingleSourceMovesList head and tail to NULL
{
	lst->head = NULL;
	lst->tail = NULL;
}

bool isEmptyListSingleSource(SingleSourceMovesList* lst) // checks if a SingleSourceMovesList is empty
{
	if (lst->head == NULL)
		return true;
	else
		return false;
}

/* inserts data into a MultipleSourceMovesListCell at the end of the list */
void insertDataToEndListAllOptions(MultipleSourceMovesList* lst, SingleSourceMovesList* characterOptionPlayList, MultipleSourceMovesListCell* next)
{
	MultipleSourceMovesListCell* newTail;
	newTail = createNewListNodeAllOptions(characterOptionPlayList, next);
	insertNodeToEndListAllOptions(lst, newTail);
}

/* creates a new MultipleSourceMovesListCell with given parameters */
MultipleSourceMovesListCell* createNewListNodeAllOptions(SingleSourceMovesList* characterOptionPlayList, MultipleSourceMovesListCell* next)
{
	SingleSourceMovesListCell* curr = characterOptionPlayList->head;

	MultipleSourceMovesListCell* res = (MultipleSourceMovesListCell*)malloc(sizeof(MultipleSourceMovesListCell));
	res->single_source_moves_list = (SingleSourceMovesList*)malloc(sizeof(SingleSourceMovesList)); //////checks if we need to allocate

	if (!res || !res->single_source_moves_list) {
		allocationFailure();
	}
	makeEmptyListSingleSource(res->single_source_moves_list);

	while (curr != NULL) {
		
		checkersPos* newPos = (checkersPos*)malloc(sizeof(checkersPos)); // Create a new checkersPos instance and copy the values
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

void insertNodeToEndListAllOptions(MultipleSourceMovesList* lst, MultipleSourceMovesListCell* tail) // insert the SingleSourceMovesListCell at the end of the list
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

void makeEmptyListAllOptions(MultipleSourceMovesList* lst) // initializes MultipleSourceMovesList head and tail to NULL
{
	lst->head = NULL;
	lst->tail = NULL;
}

bool isEmptyListAllOptions(MultipleSourceMovesList* lst) // checks if a MultipleSourceMovesList is empty
{
	if (lst->head == NULL)
		return true;
	else
		return false;
}

void freeSingleSourceMovesList(SingleSourceMovesList* list) // free SingleSourceMovesList
{
	SingleSourceMovesListCell* curr = list->head;
	SingleSourceMovesListCell* next;

	while (curr != NULL)
	{
		next = curr->next;
		free(curr->position);
		free(curr);
		curr = next;
	}
	free(list);
}

void freeMultipleSourceMovesList(MultipleSourceMovesList* list) // free MultipleSourceMovesList
{
	MultipleSourceMovesListCell* curr = list->head;
	MultipleSourceMovesListCell* next;
	while (curr != NULL)
	{
		next = curr->next;
		freeSingleSourceMovesList(curr->single_source_moves_list);
		free(curr);
		curr = next;
	}
	free(list);
}
