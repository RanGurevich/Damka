#ifndef __MOVEMENTS_AND_LISTS_H
#define __MOVEMENTS_AND_LISTS_H

#include "Utills.h"

SingleSourceMovesList* FindSingleSourceOptimalMove(SingleSourceMovesTree* moves_tree);
int FindSingleSourceOptimalMoveHelper(SingleSourceMovesTreeNode* treeNode, SingleSourceMovesList* list, Player currPlayer);
int findTheBiggerCapture(SingleSourceMovesTreeNode* treeNode);
MultipleSourceMovesList* FindAllPossiblePlayerMoves(Board board, Player player);

#endif