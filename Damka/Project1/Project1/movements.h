#ifndef __MOVEMENTS_H
#define __MOVEMENTS_H

#include "utills.h"

SingleSourceMovesList* FindSingleSourceOptimalMove(SingleSourceMovesTree* moves_tree);
int FindSingleSourceOptimalMoveHelper(SingleSourceMovesTreeNode* treeNode, SingleSourceMovesList* list, Player currPlayer);
int findTheBiggerCapture(SingleSourceMovesTreeNode* treeNode);
MultipleSourceMovesList* FindAllPossiblePlayerMoves(Board board, Player player);

#endif