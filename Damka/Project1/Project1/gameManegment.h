#ifndef __GAME_MANEGMENT_H
#define __GAME_MANEGMENT_H

#include "Structs.h"
#include "Utills.h"
#include "MovementsAndLists.h"
#include "ListsUtills.h"
#include "BoardAndTrees.h"

void Turn(Board board, Player player);
SingleSourceMovesList* findBestMove(MultipleSourceMovesList* allMoves, Player playTurn);
void setNewBoard(Board board, SingleSourceMovesList* bestPlay, Player player);
void printData(SingleSourceMovesList* bestPlay, Board board);
void PlayGame(Board board, Player starting_playing);
bool isWon(Board board, Player player);
void printBoard(Board board);
void printGameStart(Board board);

#endif