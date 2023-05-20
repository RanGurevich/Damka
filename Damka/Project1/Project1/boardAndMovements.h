#pragma once
#include "structs.h"
#include "utills.h"

void allocationFailure();
void duplicateBoard(Board board, SingleSourceMovesTreeNode* moveNode);
SingleSourceMovesTree* FindSingleSourceMove(Board board, checkersPos* src);
void updateBoard(Board board, checkersPos* toMovePoint, checkersPos* toRemove1, checkersPos* toRemove2, SingleSourceMovesTreeNode* moveNode);
SingleSourceMovesTree* FindSingleSourceMoveHelper(Board board, checkersPos* src, int totalCaptures);
SingleSourceMovesTreeNode* buildNewMoveNode(Board board, checkersPos* src, int totalCaptures, SingleSourceMovesTreeNode* singleMove0, SingleSourceMovesTreeNode* singleMove1);

