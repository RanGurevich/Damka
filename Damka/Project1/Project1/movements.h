#pragma once
#include "utills.h"

SingleSourceMovesList* FindSingleSourceOptimalMove(SingleSourceMovesTree* moves_tree);
int FindSingleSourceOptimalMoveHelper(SingleSourceMovesTreeNode* treeNode, SingleSourceMovesList* list);
MultipleSourceMovesList* FindAllPossiblePlayerMoves(Board board, Player player);
findTheBiggerCapture(SingleSourceMovesTreeNode* treeNode);
SingleSourceMovesList* findBestMove(MultipleSourceMovesList* allMoves, Player playTurn);