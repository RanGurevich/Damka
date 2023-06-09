#include "movements.h"
#include "utills.h"
#include "structs.h"
#include "Lists.h"
#include "movements.h"
#include "boardAndMovements.h"


//////////////////////////checks for united with List.C

/* FindSingleSourceOptimalMove finds the optimal move for a single checkers piece 
and returns a list of the best path according to the given rules */
SingleSourceMovesList* FindSingleSourceOptimalMove(SingleSourceMovesTree* moves_tree)
{
	SingleSourceMovesList* list = (SingleSourceMovesList*)malloc(sizeof(SingleSourceMovesList));
	if (!list) 
		allocationFailure();

	makeEmptyListSingleSource(list);

	if (moves_tree && moves_tree->source) 
	{
		// recursively find the optimal move
		FindSingleSourceOptimalMoveHelper(moves_tree->source, list, getCharOnBoard(moves_tree->source->board, moves_tree->source->pos));
	}
	return list;
}

/* helper function to find the optimal move for a single source */
int FindSingleSourceOptimalMoveHelper(SingleSourceMovesTreeNode* treeNode, SingleSourceMovesList* list, Player currPlayer)
{
	int capturesRight = 0, capturesLeft = 0;
	if (!treeNode) {
		return 0;
	}
	/* find the number of captures for the left and right moves for choosing the correct path after it*////////////////////////?????? does it right??
	capturesRight = !treeNode->next_move[RIGHT] ? -1 : findTheBiggerCapture(treeNode->next_move[RIGHT]); 
	capturesLeft = !treeNode->next_move[LEFT] ? -1 : findTheBiggerCapture(treeNode->next_move[LEFT]); 
	insertDataToEndListSingleSource(list, treeNode->pos, treeNode->total_captures_so_far, NULL);

	if (capturesRight > capturesLeft) //conditions for choosing the correct path
	{
		if (treeNode->next_move[RIGHT])
			FindSingleSourceOptimalMoveHelper(treeNode->next_move[RIGHT], list, currPlayer);
	}
	else if (capturesRight == capturesLeft)
	{
		if (currPlayer == PLAYER_T)
		{
			FindSingleSourceOptimalMoveHelper(treeNode->next_move[RIGHT], list, currPlayer);
			//not sure if should be free here////////////////////////////////////
		}
		else
		{
			FindSingleSourceOptimalMoveHelper(treeNode->next_move[LEFT], list, currPlayer);
			//not sure if should be free here///////////////////////////////////
		}
	}
	else
	{
		if (treeNode->next_move[LEFT])
			FindSingleSourceOptimalMoveHelper(treeNode->next_move[LEFT], list, currPlayer);
		//not sure if should be free here///////////////////////////////////////
	}
}

int findTheBiggerCapture(SingleSourceMovesTreeNode* treeNode) // findTheBiggerCapture function finds the maximum number of captures in a subtree of possible moves /
{
	if (!treeNode) 
		return 0;
	
	if (!treeNode->next_move[LEFT] && !treeNode->next_move[RIGHT]) // case for MoveTreeNode without childens
		return treeNode->total_captures_so_far;

	int leftHeight = findTheBiggerCapture(treeNode->next_move[LEFT]);
	int rightHeight = findTheBiggerCapture(treeNode->next_move[RIGHT]);

	return (leftHeight > rightHeight ? leftHeight : rightHeight); // Return the maximum of the left and right values 
}

/* FindAllPossiblePlayerMoves function finds all possible moves for a player on a given board */
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

	for (i = 0; i < BOARD_SIZE; i++) // loop over all positions on the board 
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			if (board[i][j] == player)
			{
				pos->row = i + 'A';
				pos->col = j + '0';
				moveTree = FindSingleSourceMove(board, pos); // call for creating a MoveTree
				optimalMoves = FindSingleSourceOptimalMove(moveTree); // call for finding the best path in the tree
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
	//free(pos);
		
	return playerAllOptionsList;
}