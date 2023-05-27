#include "movements.h"
#include "utills.h"
#include "structs.h"
#include "Lists.h"
#include "movements.h"

SingleSourceMovesList* FindSingleSourceOptimalMove(SingleSourceMovesTree* moves_tree) {
	SingleSourceMovesList* list = (SingleSourceMovesList*)(malloc(sizeof(SingleSourceMovesList)));
	if (!list) {
		allocationFailure();
	}
	makeEmptyListSingleSource(list);
	FindSingleSourceOptimalMoveHelper(moves_tree->source, list, getCharOnBoard(moves_tree->source->board, moves_tree->source->pos));
	return list;
}

int numbersOfNodesInTree(SingleSourceMovesTreeNode* treeNode) {
	int right = 0;
	int left = 0;
	if (!treeNode)
	{
		return 0;
	}
	return numbersOfNodesInTree(treeNode->next_move[RIGHT]) + numbersOfNodesInTree(treeNode->next_move[LEFT]) +1;
}

int FindSingleSourceOptimalMoveHelper(SingleSourceMovesTreeNode* treeNode, SingleSourceMovesList* list, Player currPlayer) {
	int captureRight = 0, captureLeft = 0;
	if (!treeNode) {
		return 0;
	}
	captureRight = numbersOfNodesInTree(treeNode->next_move[RIGHT]); //1
	captureLeft = numbersOfNodesInTree(treeNode->next_move[LEFT]); // 1
	insertDataToEndListSingleSource(list, treeNode->pos, treeNode->total_captures_so_far, NULL);
	if (captureRight > captureLeft) 
	{
		if(treeNode->next_move[RIGHT])
		FindSingleSourceOptimalMoveHelper(treeNode->next_move[RIGHT], list, currPlayer);
		//to do freelist
	}
	else if (captureRight == captureLeft)
	{
		if (currPlayer == PLAYER_T)
		{
			FindSingleSourceOptimalMoveHelper(treeNode->next_move[RIGHT], list, currPlayer);
			//to do freelist
		}
		else
		{
			FindSingleSourceOptimalMoveHelper(treeNode->next_move[LEFT], list, currPlayer);
			//to do freelist
		}

	}
	else
	{
		if (treeNode->next_move[LEFT])
		FindSingleSourceOptimalMoveHelper(treeNode->next_move[LEFT], list, currPlayer);
		//to do freelist
	}
}


