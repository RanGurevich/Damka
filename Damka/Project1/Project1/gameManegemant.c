#include "gameManegment.h"

 int maxCapturesInSingleMoves = 0;
 Player playerThatDidTheMaxCaptures;
 int totalCapturesT = 0;
 int totalCapturesB = 0;


void Turn(Board board, Player player) {
	MultipleSourceMovesList* allMoves = FindAllPossiblePlayerMoves(board, player);
	SingleSourceMovesList* bestPlay = findBestMove(allMoves, player);
	//printList(bestPlay);
	if (maxCapturesInSingleMoves < bestPlay->tail->captures)
	{
		maxCapturesInSingleMoves = bestPlay->tail->captures;
		playerThatDidTheMaxCaptures = player;
	}
	switch (player)
	{
	case PLAYER_T:
		totalCapturesT += bestPlay->tail->captures;
		break;
	case PLAYER_B:
		totalCapturesB += bestPlay->tail->captures;
		break;
	default:
		break;
	}
	setNewBoard(board, bestPlay, player);
	printData(bestPlay, board);

}

void printData(SingleSourceMovesList* bestPlay, Board board) {
	printf("%c%c -> %c%c \n", bestPlay->head->position->row, bestPlay->head->position->col + 1, bestPlay->tail->position->row , bestPlay->tail->position->col + 1);
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

void PlayGame(Board board, Player starting_playing) 
{
	int i, numOfMovesB = 0, numOfMovesT = 0;
	bool winning = false;

	while(!winning)
	{
		starting_playing == PLAYER_T ? numOfMovesT++ : numOfMovesB++;
		printf("\n%c's turn: \n", starting_playing);
		Turn(board, starting_playing);
		if (isWon(board, starting_playing)) 
			winning = true;
		else
			starting_playing = (starting_playing == PLAYER_B ? PLAYER_T : PLAYER_B);
	}
	printf("\n%c wins!\n", starting_playing);
	printf("%c preformed %d moves\n",starting_playing, starting_playing == PLAYER_T ? numOfMovesT : numOfMovesB);
	printf("%c performed the highest number of captures in a single move - %d", playerThatDidTheMaxCaptures, maxCapturesInSingleMoves);
}

bool isWon(Board board, Player player) {
	int i, j;
	
	if (totalCapturesT  == NUMBER_OF_TOOLS || totalCapturesB == NUMBER_OF_TOOLS)
	{
		return true;
	}
	for (j = 0; j < BOARD_SIZE; j++) {
		if ((player == PLAYER_T && board[7][j] == player) ||
			(player != PLAYER_T && board[0][j] == player)) {
			return true;
		}
	}

	return false;
}

void printBoard(Board board)
{
	printf(" +-+-+-+-+-+-+-+-+-+\n");
	printf(" + |1|2|3|4|5|6|7|8|\n");
	printf(" +-+-+-+-+-+-+-+-+-+\n");
	for (int row = 0; row < BOARD_SIZE; row++)
	{
		printf(" |%c|", 'A' + row);
		for (int col = 0; col < BOARD_SIZE; col++)
		{
			printf("%c|", board[row][col]);
		}
		printf("\n");
		printf(" +-+-+-+-+-+-+-+-+-+\n");
	}
}


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


//bool isWon(Board board, Player player) {
//	int i, j;
//
//	if (player == PLAYER_T)
//	{
//		for (i = 7, j = 0; j < BOARD_SIZE; j++)
//		{
//			if (board[i][j] == player) 
//			{
//				return true;
//			}
//			
//		}
//	}
//	else
//	{
//		for (i = 0, j = 0; j < BOARD_SIZE; j++)
//		{
//			if (board[i][j] == player)
//			{
//				return true;
//			}
//		}
//	}
//
//	//
//
//
//	////if (player == PLAYER_T)
//	////{
//	////	for (i ==7,j=0; i< BOARD_SIZE - 1;j++ )
//	////}
//	//int indexRunWinCheck;
//	//for (indexRunWinCheck = 0; indexRunWinCheck < BOARD_SIZE; indexRunWinCheck++)
//	//{
//	//	for ( j = 0; j < BOARD_SIZE; j++)
//	//	{
//	//		printf("j: %d %c |", j, board[player == PLAYER_T ? BOARD_SIZE - 1 : 0][j]);
//	//	}
//	//	printf("\n");
//	//	if(board[player == PLAYER_T ? BOARD_SIZE - 1 : 0][j] == player != ' ')
//	//	if (board[player == PLAYER_T ? BOARD_SIZE - 1 : 0][j] == player) {
//	//		return true;
//	//	}
//	//}
//	return false;
//
//}