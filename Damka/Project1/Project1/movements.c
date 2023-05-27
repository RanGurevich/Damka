#include "movements.h"
#include "utills.h"
#include "structs.h"
#include "Lists.h"

SingleSourceMovesList* FindSingleSourceOptimalMove(SingleSourceMovesTree* moves_tree) {
	SingleSourceMovesList* list = (SingleSourceMovesList*)(malloc(sizeof(SingleSourceMovesList)));
	if (!list) {
		allocationFailure();
	}
	makeEmptyListSingleSource(list);
	FindSingleSourceOptimalMoveHelper(moves_tree->source, list);
}

int FindSingleSourceOptimalMoveHelper(SingleSourceMovesTreeNode* treeNode, SingleSourceMovesList* list) {
	int captureRight = 0, captureLeft = 0;
	if (treeNode->next_move[LEFT] && treeNode->next_move[RIGHT])
	{
		return treeNode->total_captures_so_far;
	}
	captureRight = FindSingleSourceOptimalMoveHelper(treeNode->next_move[RIGHT], list);
	captureLeft = FindSingleSourceOptimalMoveHelper(treeNode->next_move[LEFT], list);
	if (captureRight > captureLeft) {
		insertDataToEndListSingleSource(list, treeNode->pos, treeNode->total_captures_so_far, NULL);
		if(!treeNode->next_move[RIGHT])
		FindSingleSourceOptimalMoveHelper(treeNode->next_move[RIGHT], list);
	}
	else
	{
		insertDataToEndListSingleSource(list, treeNode->pos, treeNode->total_captures_so_far, NULL);
		if (!treeNode->next_move[LEFT])
		FindSingleSourceOptimalMoveHelper(treeNode->next_move[LEFT], list);
	}
}