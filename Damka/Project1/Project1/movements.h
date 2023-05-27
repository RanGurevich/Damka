#pragma once
#include "utills.h"

SingleSourceMovesList* FindSingleSourceOptimalMove(SingleSourceMovesTree* moves_tree);
int FindSingleSourceOptimalMoveHelper(SingleSourceMovesTreeNode* treeNode, SingleSourceMovesList* list);