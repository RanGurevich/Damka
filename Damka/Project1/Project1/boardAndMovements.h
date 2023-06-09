#pragma once
#include "structs.h"
#include "utills.h"

//void allocationFailure();
void duplicateBoard(Board board, SingleSourceMovesTreeNode* moveNode);
SingleSourceMovesTree* FindSingleSourceMove(Board board, checkersPos* src);
SingleSourceMovesTreeNode* FindSingleSourceMoveHelper(Board board, checkersPos* src, int totalCaptures);
void updateBoard(Board board, checkersPos* toMovePoint, checkersPos* toRemove1, checkersPos* toRemove2, SingleSourceMovesTreeNode* moveNode);
SingleSourceMovesTreeNode* buildNewMoveNode(Board board, checkersPos* src, int totalCaptures, SingleSourceMovesTreeNode* leftNode, SingleSourceMovesTreeNode* rightNode);
void regularMove(SingleSourceMovesTreeNode* moveNode, checkersPos* newPosition, checkersPos* src, Board board, int totalCaptures, int playOptionIndex);
SingleSourceMovesTreeNode* captureMove(SingleSourceMovesTreeNode* moveNode, checkersPos* capturedPlayer, checkersPos* capturePos, checkersPos* src, Board board, int totalCaptures, int playOptionIndex);
void printBoard(Board board);
void allocationsPosAndCap(checkersPos** newPositionRight, checkersPos** newPositionLeft, checkersPos** captureMovingPositionRight, checkersPos** captureMovingPositionLeft);

//void allocationsPosAndCap(checkersPos* newPositionRight, checkersPos* newPositionLeft, checkersPos* captureMovingPositionRight, checkersPos* captureMovingPositionLeft);
void setPosAndCap(checkersPos* src, checkersPos* newPositionRight, checkersPos* newPositionLeft, checkersPos* captureMovingPositionRight, checkersPos* captureMovingPositionLeft, int toolMovingPosition);
void movePlayerLeft(Board board, SingleSourceMovesTreeNode* moveNode, checkersPos* src, checkersPos* captureMovingPositionLeft, checkersPos* newPositionLeft, char opponentPlayer, int totalCaptures);
void movePlayerRight(Board board, SingleSourceMovesTreeNode* moveNode, checkersPos* src, checkersPos* captureMovingPositionLeft, checkersPos* newPositionLeft, char opponentPlayer, int totalCaptures);
bool checkPosValid(checkersPos* src);
void allocationFailure();
void duplicateBoard(Board board, SingleSourceMovesTreeNode* moveNode);
void regularMove(SingleSourceMovesTreeNode* moveNode, checkersPos* newPosition, checkersPos* src, Board board, int totalCaptures, int playOptionIndex);
void printBoard(Board board);