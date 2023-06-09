#ifndef __BOARD_AND_MOVEMENTS_H
#define __BOARD_AND_MOVEMENTS_H

#include "structs.h"
#include "utills.h"

SingleSourceMovesTree* FindSingleSourceMove(Board board, checkersPos* src);
SingleSourceMovesTreeNode* FindSingleSourceMoveHelper(Board board, checkersPos* src, int totalCaptures);
void allocationsPosAndCap(checkersPos** newPositionRight, checkersPos** newPositionLeft, checkersPos** captureMovingPositionRight, checkersPos** captureMovingPositionLeft);
void setPosAndCap(checkersPos* src, checkersPos* newPositionRight, checkersPos* newPositionLeft, checkersPos* captureMovingPositionRight, checkersPos* captureMovingPositionLeft, int toolMovingPosition);
void movePlayerLeft(Board board, SingleSourceMovesTreeNode* moveNode, checkersPos* src, checkersPos* captureMovingPositionLeft, checkersPos* newPositionLeft, char opponentPlayer, int totalCaptures);
void movePlayerRight(Board board, SingleSourceMovesTreeNode* moveNode, checkersPos* src, checkersPos* captureMovingPositionRight, checkersPos* newPositionRight, char opponentPlayer, int totalCaptures);
void regularMove(SingleSourceMovesTreeNode* moveNode, checkersPos* newPosition, checkersPos* src, Board board, int totalCaptures, int playOptionIndex);
SingleSourceMovesTreeNode* captureMove(SingleSourceMovesTreeNode* moveNode, checkersPos* capturedPlayer, checkersPos* capturePos, checkersPos* src, Board board, int totalCaptures, int playOptionIndex);
SingleSourceMovesTreeNode* buildNewMoveNode(Board board, checkersPos* src, int totalCaptures, SingleSourceMovesTreeNode* leftNode, SingleSourceMovesTreeNode* rightNode);
void updateBoard(Board board, checkersPos* newPos, checkersPos* currPos, checkersPos* capturedPos);
void duplicateBoard(Board board, SingleSourceMovesTreeNode* moveNode);
void freeMoveTree(SingleSourceMovesTree* tree);
void freeMoveTreeNodeHelper(SingleSourceMovesTreeNode* source);

#endif