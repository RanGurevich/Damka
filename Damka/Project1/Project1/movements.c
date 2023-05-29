#include "movements.h"
#include "utills.h"
#include "structs.h"
#include "Lists.h"
#include "movements.h"
#include "boardAndMovements.h"

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

MultipleSourceMovesList* FindAllPossiblePlayerMoves(Board board, Player player) {
	int i, j;
	MultipleSourceMovesList* playerAllOptionsList = (MultipleSourceMovesList*)(malloc(sizeof(MultipleSourceMovesList)));
	checkersPos* pos = (checkersPos*)(malloc(sizeof(checkersPos)));
	if (!playerAllOptionsList || pos) {
		allocationFailure();
	}
	makeEmptyListAllOptions(playerAllOptionsList);
	for (i = 0; i < SIZE_MAX; i++)
	{
		for ( j = 0; j < SIZE_MAX; j++)
		{
			if (board[i][j] == player)
			{
				pos->col = i + '0';
				pos->row = j + 'A';
				insertDataToEndListAllOptions(playerAllOptionsList,
				FindSingleSourceOptimalMove(FindSingleSourceMove(board, pos)), NULL);
			}
		}
	}
	free(pos);
	return playerAllOptionsList;
}


