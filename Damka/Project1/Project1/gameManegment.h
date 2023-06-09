#pragma once
#include "structs.h"
#include "utills.h"
#include "movements.h"
#include "Lists.h"
#include "boardAndMovements.h"

void Turn(Board board, Player player);
SingleSourceMovesList* findBestMove(MultipleSourceMovesList* allMoves, Player playTurn);
void setNewBoard(Board board, SingleSourceMovesList* bestPlay, Player player);
void PlayGame(Board board, Player starting_playing);
void printData(SingleSourceMovesList* bestPlay, Board board);
void printBoard(Board board);
bool isWon(Board board, Player player);
