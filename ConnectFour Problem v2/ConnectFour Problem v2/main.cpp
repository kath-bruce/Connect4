#include <vector>
#include <iostream>

enum SLOTSTATE {
	NONE, PLAYER1, PLAYER2
};

enum BOARDSTATE {
	INPLAY, PLAYER1WINS, PLAYER2WINS, DRAW
};

std::vector< std::vector<SLOTSTATE> > board;
//BOARDSTATE bState = INPLAY;
const int N_ROWS = 6;
const int N_COLS = 7;
int roundCounter = 0;
int lastRow;
int nonEmpty = 0;

bool playAgain = true;

void initBoard()
{
	board.resize(N_ROWS);

	for (int k = 0; k < N_ROWS; k++)
		board[k].resize(N_COLS);

	for (int i = 0; i < N_ROWS; i++)
		for (int j = 0; j < N_COLS; j++)
			board[i][j] = NONE;

	roundCounter = 0;
	nonEmpty = 0;
}

void displayBoard()
{
	std::cout << "\n";

	for (int i = N_ROWS; i > -1; i--)
	{
		if (i < N_ROWS)
			std::cout << i+1 << "\t";
		else
			std::cout << "\t";

		for (int j = 0; j < N_COLS; j++)
		{
			if (i == N_ROWS)
				std::cout << j+1 << "\t";
			else
			{
				switch (board[i][j])
				{
				case NONE:
					std::cout << "-\t";
					break;

				case PLAYER1:
					std::cout << "X\t";
					break;

				case PLAYER2:
					std::cout << "O\t";
					break;

				default:
					std::cout << "|\t";
					break;
				}
			}
		}

		std::cout << "\n\n\n";
	}

	std::cout << "\n\n\n";
}

void addChip(int userInput, int currentPlayer)
{
	//for loop to find first none slot state in column

	for (int i = 0; i < N_ROWS; i++)
	{
		if (board[i][userInput] == NONE)
		{
			if (currentPlayer == 1)
				board[i][userInput] = PLAYER1;
			else if (currentPlayer == 2)
				board[i][userInput] = PLAYER2;

			lastRow = i;
			nonEmpty++;
			return;
		}
	}
}

inline BOARDSTATE checkWinCount(int winCount, SLOTSTATE currentPlayerSlot)
{
	if (winCount >= 4)
	{
		if (currentPlayerSlot == PLAYER1)
			return PLAYER1WINS;
		else if (currentPlayerSlot == PLAYER2)
			return PLAYER2WINS;
	}

	return INPLAY;
}

//horizontal win condition check
BOARDSTATE checkHorizontalWinCondition(SLOTSTATE currentPlayerSlot, int &winCount, int currentSlot) 
{
	int prevSlot = currentSlot - 1;

	while (prevSlot >= 0 && board[lastRow][prevSlot] == currentPlayerSlot)
	{
		winCount++;
		prevSlot--;
	}

	BOARDSTATE currentBoardState = checkWinCount(winCount, currentPlayerSlot);

	if (currentBoardState != INPLAY)
		return currentBoardState;

	prevSlot = currentSlot + 1;

	while (prevSlot <= N_COLS - 1 && board[lastRow][prevSlot] == currentPlayerSlot)
	{
		winCount++;
		prevSlot++;
	}

	currentBoardState = checkWinCount(winCount, currentPlayerSlot);

	if (currentBoardState != INPLAY)
		return currentBoardState;
}

//vertical win condition check
BOARDSTATE checkVerticalWinCondition(SLOTSTATE currentPlayerSlot, int &winCount, int currentSlot)
{
	int prevRow = lastRow - 1;

	while (prevRow >= 0 && board[prevRow][currentSlot] == currentPlayerSlot)
	{
		winCount++;
		prevRow--;
	}

	BOARDSTATE currentBoardState = checkWinCount(winCount, currentPlayerSlot);

	if (currentBoardState != INPLAY)
		return currentBoardState;

	prevRow = lastRow + 1;

	while (prevRow <= N_ROWS - 1 && board[prevRow][currentSlot] == currentPlayerSlot)
	{
		winCount++;
		prevRow++;
	}

	currentBoardState = checkWinCount(winCount, currentPlayerSlot);

	if (currentBoardState != INPLAY)
		return currentBoardState;
}

BOARDSTATE checkTRBLDiagWinCondition(SLOTSTATE currentPlayerSlot, int &winCount, int currentSlot)
{
	int prevSlot = currentSlot - 1;
	int prevRow = lastRow - 1;

	while (prevRow >= 0 && prevSlot >= 0 && board[prevRow][prevSlot] == currentPlayerSlot)
	{
		winCount++;
		prevRow--;
		prevSlot--;
	}

	BOARDSTATE currentBoardState = checkWinCount(winCount, currentPlayerSlot);

	if (currentBoardState != INPLAY)
		return currentBoardState;

	prevSlot = currentSlot + 1;
	prevRow = lastRow + 1;

	while (prevRow <= N_ROWS - 1 && prevSlot <= N_COLS - 1 && board[prevRow][prevSlot] == currentPlayerSlot)
	{
		winCount++;
		prevRow++;
		prevSlot++;
	}

	currentBoardState = checkWinCount(winCount, currentPlayerSlot);

	if (currentBoardState != INPLAY)
		return currentBoardState;
}

BOARDSTATE checkBRTLDiagWinCondition(SLOTSTATE currentPlayerSlot, int &winCount, int currentSlot)
{
	int prevSlot = currentSlot - 1;
	int prevRow = lastRow + 1;

	while (prevRow <= N_ROWS - 1 && prevSlot >= 0 && board[prevRow][prevSlot] == currentPlayerSlot)
	{
		winCount++;
		prevRow++;
		prevSlot--;
	}

	BOARDSTATE currentBoardState = checkWinCount(winCount, currentPlayerSlot);

	if (currentBoardState != INPLAY)
		return currentBoardState;

	prevSlot = currentSlot + 1;
	prevRow = lastRow - 1;

	while (prevRow >= 0 && prevSlot <= N_COLS - 1 && board[prevRow][prevSlot] == currentPlayerSlot)
	{
		winCount++;
		prevRow--;
		prevSlot++;
	}

	currentBoardState = checkWinCount(winCount, currentPlayerSlot);

	if (currentBoardState != INPLAY)
		return currentBoardState;
}

BOARDSTATE checkBoard(int currentPlayer, int userInput)
{
	//if roundcounter is less than 7, return INPLAY
	if (roundCounter < 7)
		return INPLAY;

	SLOTSTATE currentPlayerSlot = static_cast<SLOTSTATE>(currentPlayer);
	int winCount = 1;

	//across win condition
	BOARDSTATE currentBoardState = checkHorizontalWinCondition(currentPlayerSlot, winCount, userInput);

	if (currentBoardState != INPLAY)
		return currentBoardState;
	else
		winCount = 1;

	//vertical win condition
	currentBoardState = checkVerticalWinCondition(currentPlayerSlot, winCount, userInput);

	if(currentBoardState != INPLAY)
		return currentBoardState;
	else
		winCount = 1;

	//toprightbottomleft diagonal win condition
	currentBoardState = checkTRBLDiagWinCondition(currentPlayerSlot, winCount, userInput);

	if(currentBoardState != INPLAY)
		return currentBoardState;
	else
		winCount = 1;

	
	//bottomrighttopleft diagonal win condition
	currentBoardState = checkBRTLDiagWinCondition(currentPlayerSlot, winCount, userInput);

	if(currentBoardState != INPLAY)
		return currentBoardState;
	else
		winCount = 1;

	//full state - loop through and count non empty slots
	//if no of non empty slots == n_cols * n_rows, return DRAW
	if (nonEmpty == (N_COLS * N_ROWS))
		return DRAW;

	return INPLAY;
}

void checkPlayAgain()
{
	std::cout << "Play again?\n";

	std::cout << "Enter 'y' to play again or 'n' to quit: ";

	char playAgainUserInput;
	std::cin >> playAgainUserInput;

	while (playAgainUserInput != 'n' && playAgainUserInput != 'y')
	{
		std::cin.ignore(32767,'\n');

		std::cout << "Invalid input\n";
		std::cout << "Enter 'y' to play again or 'n' to quit: ";
		std::cin >> playAgainUserInput;
	}

	if (playAgainUserInput == 'y')
	{
		initBoard();
		displayBoard();
	}
	else if (playAgainUserInput == 'n')
	{
		playAgain = false;
	}
}

void makeMove()
{
	std::cout << "Enter a number between 1-7 to play or 0 to quit\n";
	int currentPlayer;

	roundCounter++;

	int userInput;
	bool validInput = false;
	bool legalInput = false;

	while (!validInput || !legalInput)
	{
		if (roundCounter % 2 == 0)
		{
			currentPlayer = 2;
			std::cout << "Player 2, enter column: ";
		}
		else
		{
			currentPlayer = 1;
			std::cout << "Player 1, enter column: ";
		}

		std::cin >> userInput;

		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(32767,'\n');
			std::cout << "Invalid input\n";
		}
		else if (userInput < 0 || userInput > 7)
			std::cout << "Invalid input\n";
		else if (userInput == 0)
			exit(0);
		else 
			validInput = true;

		if (!validInput)
			continue;

		userInput--;

		if (board[N_ROWS - 1][userInput] == NONE)
			legalInput = true;
		else
			std::cout << "Invalid input\n";
	}

	//addchip
	addChip(userInput, currentPlayer);

	displayBoard();

	//check board
	BOARDSTATE currentBoardState = checkBoard(currentPlayer, userInput);

	if (currentBoardState != INPLAY)
	{
		if (currentBoardState == PLAYER1WINS)
			std::cout << "Player 1 WINS!\n";
		else if (currentBoardState == PLAYER2WINS)
			std::cout << "Player 2 WINS!\n";
		else if (currentBoardState == DRAW)
			std::cout << "DRAW!\n";

		checkPlayAgain();
	}
}

void main(int argc, char** argv)
{
	initBoard();
	displayBoard();

	while (playAgain)
	{
		makeMove();
	}
}