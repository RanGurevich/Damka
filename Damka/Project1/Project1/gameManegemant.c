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
	MultipleSourceMovesList* allMoves = FindAllPossiblePlayerMoves(board, player);
	SingleSourceMovesList* bestPlay = findBestMove(allMoves, player);
	//printList(bestPlay);
	setNewBoard(board, bestPlay, player);
	printData(bestPlay, board);

}

void printData(SingleSourceMovesList* bestPlay, Board board) {
	printf("%c%c -> %c%c \n", bestPlay->head->position->row, bestPlay->head->position->col, bestPlay->tail->position->row, bestPlay->tail->position->col);
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

void PlayGame(Board board, Player starting_playing) {
	int i;
	while(isWon(board, starting_playing))
	{
		printf("%c's turn: \n", starting_playing);
		Turn(board, starting_playing);
		starting_playing = (starting_playing == PLAYER_B ? PLAYER_T : PLAYER_B);

	}
}

bool isWon(Board board, Player player) {
	int i, j;

	if (player == PLAYER_T)
	{
		for (i ==7,j=0; i< BOARD_SIZE - 1;j++ )
	}
	int indexRunWinCheck;
	for (indexRunWinCheck = 0; indexRunWinCheck < BOARD_SIZE; indexRunWinCheck++)
	{
		if(board[indexRunWinCheck][])
		if (board[player == PLAYER_T ? BOARD_SIZE - 1 : 0][indexRunWinCheck] == player) {
			return true;
		}
	}
	return false;

}