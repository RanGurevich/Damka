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
	printList(bestPlay);
}