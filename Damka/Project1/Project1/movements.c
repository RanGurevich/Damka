#include "movements.h"
#include "utills.h"
#include "structs.h"
#include "Lists.h"
#include "movements.h"
#include "boardAndMovements.h"


//////////////////////////checks for united with List.C


SingleSourceMovesList* FindSingleSourceOptimalMove(SingleSourceMovesTree* moves_tree)
{
	SingleSourceMovesList* list = (SingleSourceMovesList*)malloc(sizeof(SingleSourceMovesList));
	if (!list) 
		allocationFailure();
	makeEmptyListSingleSource(list);

	if (moves_tree->source) 
	{
		FindSingleSourceOptimalMoveHelper(moves_tree->source, list, getCharOnBoard(moves_tree->source->board, moves_tree->source->pos));
	}

	return list;
}

int FindSingleSourceOptimalMoveHelper(SingleSourceMovesTreeNode* treeNode, SingleSourceMovesList* list, Player currPlayer)
{
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

int findTheBiggerCapture(SingleSourceMovesTreeNode* treeNode)
{
	if (!treeNode) 
		return 0;
	
	if (!treeNode->next_move[LEFT] && !treeNode->next_move[RIGHT])
		return treeNode->total_captures_so_far;

	int leftHeight = findTheBiggerCapture(treeNode->next_move[LEFT]);
	int rightHeight = findTheBiggerCapture(treeNode->next_move[RIGHT]);

	return  (leftHeight > rightHeight ? leftHeight : rightHeight);
}

MultipleSourceMovesList* FindAllPossiblePlayerMoves(Board board, Player player) 
{
	int i, j;

	SingleSourceMovesTree* moveTree = NULL;
	SingleSourceMovesList* optimalMoves = NULL;
	SingleSourceMovesList optimalMovesToSend;

	MultipleSourceMovesList* playerAllOptionsList = (MultipleSourceMovesList*)malloc(sizeof(MultipleSourceMovesList));
	checkersPos* pos = (checkersPos*)malloc(sizeof(checkersPos));

	if (!playerAllOptionsList || !pos) 
		allocationFailure();

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
				//printListAllOptions(optimalMoves);
				free(optimalMoves);
			}
			//printf("i %d j %d\n", i, j);
		}
	}

	freeMoveTree(moveTree);
	
	return playerAllOptionsList;
}


//SingleSourceMovesList* optimalMoves = (SingleSourceMovesList*)malloc(sizeof(SingleSourceMovesList));
//SingleSourceMovesTree *moveTree = (SingleSourceMovesTree*)malloc(sizeof(SingleSourceMovesTree)); //check allox


/*int right = 0; ///////////////////////check with ran
	int left = 0;
	if (!treeNode)
	{
		return 0;
	}
	return numbersOfNodesInTree(treeNode->next_move[RIGHT]) + numbersOfNodesInTree(treeNode->next_move[LEFT]) + 1;*/