#include "gameManegment.h"

 int maxCapturesInSingleMoves = 0;
 Player playerThatDidTheMaxCaptures;
 int totalCapturesT = 0;
 int totalCapturesB = 0;


void Turn(Board board, Player player) //Turn function performs a turn for a player on a given board 
{
	MultipleSourceMovesList* allMoves = FindAllPossiblePlayerMoves(board, player); // find all possible moves for the player on the board 
	SingleSourceMovesList* bestPlay = findBestMove(allMoves, player); // find the best move for the player 

	if (maxCapturesInSingleMoves < bestPlay->tail->captures) // update maximum captures if the current move has more captures
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
	setNewBoard(board, bestPlay, player); // update board
	printData(bestPlay, board);
	
	freeMultipleSourceMovesList(allMoves);
	////////////////freeSingleSourceMovesList(bestPlay);
}

/* findBestMove finds the best move for a player from a list of all possible moves */
SingleSourceMovesList* findBestMove(MultipleSourceMovesList* allMoves, Player playTurn)
{
	MultipleSourceMovesListCell* currAllMoves = allMoves->head;
	SingleSourceMovesList* maxSingleMove = currAllMoves->single_source_moves_list;
	int maxCaptures = currAllMoves->single_source_moves_list->tail->captures;
	int currentCapture;
	currAllMoves = currAllMoves->next;

	while (currAllMoves) // loop over all moves in the list
	{
		currentCapture = currAllMoves->single_source_moves_list->tail->captures;
		if (playTurn == PLAYER_T ? maxCaptures <= currentCapture : maxCaptures < currentCapture) //update the max caputes
		{
			maxCaptures = currAllMoves->single_source_moves_list->tail->captures;
			maxSingleMove = currAllMoves->single_source_moves_list;
		}
		currAllMoves = currAllMoves->next;
	}
	return maxSingleMove;
}

/* setNewBoard updates the board according to the best move that was chosing via the findBestMove*/
void setNewBoard(Board board, SingleSourceMovesList* bestPlay, Player player) 
{
	SingleSourceMovesListCell* curr = bestPlay->head->next;
	SingleSourceMovesListCell* currBefore = bestPlay->head;
	checkersPos captureToRmove;

	while (curr)
	{
		if (curr->captures == 0) // update in case there are 0 captures
		{
			updateBoard(board, curr->position, currBefore->position, NULL, NULL);
		}
		else // if there are captures the function removes the captured one and save the other
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
			updateBoard(board, curr->position, currBefore->position, &captureToRmove, NULL); // update the board
		}
		curr = curr->next;
		currBefore = currBefore->next;
	}
}


void printData(SingleSourceMovesList* bestPlay, Board board) // prints the data of the move
{
	printf("%c%c -> %c%c \n", bestPlay->head->position->row, bestPlay->head->position->col + 1, bestPlay->tail->position->row , bestPlay->tail->position->col + 1);
	printBoard(board);
}

/* the main game loop where players take turns until a winning condition is met */
void PlayGame(Board board, Player starting_playing) 
{
	int i, numOfMovesB = 0, numOfMovesT = 0;
	bool winning = false;

	while(!winning)
	{
		starting_playing == PLAYER_T ? numOfMovesT++ : numOfMovesB++; // increment the number of moves for the current player
		printf("\n%c's turn: \n", starting_playing);
		Turn(board, starting_playing); // execute the turn for the current player

		if (isWon(board, starting_playing)) 
			winning = true;
		else
			starting_playing = (starting_playing == PLAYER_B ? PLAYER_T : PLAYER_B); // one of the conditions for winning the game
	}
	printf("\n%c wins!\n", starting_playing);
	printf("%c preformed %d moves\n",starting_playing, starting_playing == PLAYER_T ? numOfMovesT : numOfMovesB);
	printf("%c performed the highest number of captures in a single move - %d\n", playerThatDidTheMaxCaptures, maxCapturesInSingleMoves);
}

bool isWon(Board board, Player player) // checks if a player has won the game according to these condtions 
{
	int i, j;
	
	if (totalCapturesT  == NUMBER_OF_TOOLS || totalCapturesB == NUMBER_OF_TOOLS) // check if the total captures by either player is equal to the starting number of tools
		return true;
	
	for (j = 0; j < BOARD_SIZE; j++)  // checks if a piece, T or B reached to the last row/ first row respectively
	{
		if ((player == PLAYER_T && board[BOARD_SIZE - 1][j] == player) ||
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

void printGameStart(Board board)
{
	printf("===================================================\n");
	printf(" _    _      _                            _          \n");
	printf("| |  | |    | |                          | |         \n");
	printf("| |  | | ___| | ___ ___  _ __ ___   ___  | |_ ___    \n");
	printf("| |/\\| |/ _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\ | __/ _ \\   \n");
	printf("\\  /\\  /  __/ | (_| (_) | | | | | |  __/ | || (_) |  \n");
	printf(" \\/  \\/ \\___|_|\\___\\___/|_| |_| |_|\\___|  \\__\\___/   \n");

	printf("\n                Checkers Game                    \n");
	printf("===================================================\n\n");
	printf("\nHello! and welcone to the checkers game:\n");
	printf("In the upcoming checkers game, the computer will play against itself.\n\n");
	printf("\n                   ENJOY!\n\n");
	printf("The Initial Board:\n");
	printBoard(board);
	printf("\n");
	printf("===================================================\n\n");
}

//void printList(SingleSourceMovesList* lst)
//{
//	SingleSourceMovesListCell* curr = lst->head;
//	int count = 1;
//
//	while (curr != NULL)
//	{
//		printf("num of cell: %d \n", count);
//		printf("col: %c\n", curr->position->col);
//		printf("row:%c\n", curr->position->row);
//		printf("captures: % d\n", curr->captures);
//		printf("\n");
//		count++;
//		curr = curr->next;
//	}
//}


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