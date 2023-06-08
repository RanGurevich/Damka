#include "gameManegment.h"

void printList(SingleSourceMovesList* lst)
{
	SingleSourceMovesListCell* curr = lst->head;
	int count = 1;

	while (curr != NULL)
	{
		printf("num of cell: %d \n", count);
		printf("col: %c\n", curr->position->col);
		printf("row:%c\n", curr->position->row);
		printf("captures: % d\n", curr->captures);
		printf("\n");
		count++;
		curr = curr->next;
	}
}

void Turn(Board board, Player player) {
	printf("%c", player);
	MultipleSourceMovesList* allMoves = FindAllPossiblePlayerMoves(board, player);
	SingleSourceMovesList* bestPlay = findBestMove(allMoves, player);
	//printList(bestPlay);
	setNewBoard(board, bestPlay, player);
	printf("FINAL BOARD: \n");
	printBoard(board);
}

void setNewBoard(Board board, SingleSourceMovesList* bestPlay, Player player) {
	SingleSourceMovesListCell* curr = bestPlay->head->next;
	SingleSourceMovesListCell* currBefore = bestPlay->head;
	checkersPos captureToRmove;

	while (curr)
	{
		if (curr->captures == 0) {
			updateBoard(board, curr->position, currBefore->position, NULL, NULL);
		}
		else
		{
			switch (player)
			{
			case PLAYER_B:
				if (currBefore->position->col > curr->position->col) {
					captureToRmove.col = curr->position->col + 1;
					captureToRmove.row = curr->position->row + 1;
				}
				else
				{
					captureToRmove.col = curr->position->col - 1;
					captureToRmove.row = curr->position->row + 1;
				}
				break;
			case PLAYER_T:
				if (currBefore->position->col < curr->position->col) {
					captureToRmove.col = curr->position->col - 1;
					captureToRmove.row = curr->position->row - 1;
				}
				else
				{
					captureToRmove.col = curr->position->col + 1;
					captureToRmove.row = curr->position->row - 1;
				}
				break;
			default:
			break;
			}
			updateBoard(board, curr->position, currBefore->position, &captureToRmove, NULL);
		}
		curr = curr->next;
		currBefore = currBefore->next;
	}
 }