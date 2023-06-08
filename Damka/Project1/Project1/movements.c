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
	if (moves_tree->source) {
		FindSingleSourceOptimalMoveHelper(moves_tree->source, list, getCharOnBoard(moves_tree->source->board, moves_tree->source->pos));
	}
	return list;
}

int findTheBiggerCapture(SingleSourceMovesTreeNode* treeNode) {
	/*int right = 0;
	int left = 0;
	if (!treeNode)
	{
		return 0;
	}
	return numbersOfNodesInTree(treeNode->next_move[RIGHT]) + numbersOfNodesInTree(treeNode->next_move[LEFT]) + 1;*/
	if (!treeNode) {
		return 0;
	}

	if (!treeNode->next_move[LEFT] && !treeNode->next_move[RIGHT])
		return treeNode->total_captures_so_far;

	int leftHeight = findTheBiggerCapture(treeNode->next_move[LEFT]);
	int rightHeight = findTheBiggerCapture(treeNode->next_move[RIGHT]);

	return  (leftHeight > rightHeight ? leftHeight : rightHeight);
}

int FindSingleSourceOptimalMoveHelper(SingleSourceMovesTreeNode* treeNode, SingleSourceMovesList* list, Player currPlayer) {
	int capturesRight = 0, capturesLeft = 0;
	if (!treeNode) {
		return 0;
	}
	// check if it possible to do without the height
	capturesRight = !treeNode->next_move[RIGHT] ? -1 : findTheBiggerCapture(treeNode->next_move[RIGHT]); //1
	capturesLeft = !treeNode->next_move[LEFT] ? -1 : findTheBiggerCapture(treeNode->next_move[LEFT]); // 1
	insertDataToEndListSingleSource(list, treeNode->pos, treeNode->total_captures_so_far, NULL);
	if (capturesRight > capturesLeft)
	{
		if (treeNode->next_move[RIGHT])
			FindSingleSourceOptimalMoveHelper(treeNode->next_move[RIGHT], list, currPlayer);
		//to do freelist
	}
	else if (capturesRight == capturesLeft)
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
	SingleSourceMovesTree *moveTree = (SingleSourceMovesTree*)malloc(sizeof(SingleSourceMovesTree)); //check allox
	checkersPos* pos = (checkersPos*)(malloc(sizeof(checkersPos)));
	SingleSourceMovesList* optimalMoves = (SingleSourceMovesList*)malloc(sizeof(SingleSourceMovesList));
	SingleSourceMovesList optimalMovesToSend;
	if (!playerAllOptionsList || !pos) {
		allocationFailure();
	}
	makeEmptyListAllOptions(playerAllOptionsList);
	for (i = 0; i < BOARD_SIZE; i++)
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			if (board[i][j] == player)
			{
				pos->row = i + 'A';
				pos->col = j + '0';
				moveTree = FindSingleSourceMove(board, pos);
				optimalMoves = FindSingleSourceOptimalMove(moveTree);
				optimalMovesToSend.head = optimalMoves->head;
				optimalMovesToSend.tail = optimalMoves->tail;
				if (optimalMoves->head != optimalMoves->tail) {
					insertDataToEndListAllOptions(playerAllOptionsList, &optimalMovesToSend, NULL);
				}
				//printListAllOptionsX(optimalMoves);
			}
			//printf("i %d j %d\n", i, j);
		}
	}
	free(pos);
	return playerAllOptionsList;
}

SingleSourceMovesList* findBestMove(MultipleSourceMovesList* allMoves, Player playTurn) {
	
	MultipleSourceMovesListCell* currAllMoves = allMoves->head;
	SingleSourceMovesList* maxSingleMove = currAllMoves->single_source_moves_list;
	int maxCaptures = currAllMoves->single_source_moves_list->tail->captures;
	int currentCapture;
	currAllMoves = currAllMoves->next;
	
	while (currAllMoves)
	{
		currentCapture = currAllMoves->single_source_moves_list->tail->captures;
		if (playTurn == 'T' ? maxCaptures <= currentCapture : maxCaptures < currentCapture) {
			maxCaptures = currAllMoves->single_source_moves_list->tail->captures;
			maxSingleMove = currAllMoves->single_source_moves_list;
		}
		currAllMoves = currAllMoves->next;
	}
	return maxSingleMove;
}
