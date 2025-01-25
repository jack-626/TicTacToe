/*
  _______   _____    _____     _______               _____     _______    ____    ______
 |__   __| |_   _|  / ____|   |__   __|     /\      / ____|   |__   __|  / __ \  |  ____|
	| |      | |   | |           | |       /  \    | |           | |    | |  | | | |__
	| |      | |   | |           | |      / /\ \   | |           | |    | |  | | |  __|
	| |     _| |_  | |____       | |     / ____ \  | |____       | |    | |__| | | |____
	|_|    |_____|  \_____|      |_|    /_/    \_\  \_____|      |_|     \____/  |______|
	
	Created by Jack Bennett
	25th January 2025
*/

#include <iostream>

void drawBoard();
bool checkWin(char player);
bool checkDraw();
void chooseSpot(char player);

const char player1 = 'X';
const char player2 = 'O';

char board[3][3]
{
	{'1', '2', '3'},
	{'4', '5', '6'},
	{'7', '8', '9'}
};

int main()
{
	//Game Loop
	while (true)
	{
		drawBoard();

		//Player 1's turn
		chooseSpot(player1);
		if (checkWin(player1))
		{
			system("cls");
			drawBoard();
			std::cout << "\nPlayer " << player1 << " Wins! Congrats!" << std::endl;
			break;
		}
		if (checkDraw())
		{
			system("cls");
			drawBoard();
			std::cout << "\nIt's a draw!" << std::endl;
			break;
		}
		system("cls");

		drawBoard();

		//Player 2's turn
		chooseSpot(player2);
		if (checkWin(player2))
		{
			system("cls");
			drawBoard();
			std::cout << "\nPlayer " << player2 << " Wins! Congrats!" << std::endl;
			break;
		}
		if (checkDraw())
		{
			system("cls");
			drawBoard();
			std::cout << "\nIt's a draw!" << std::endl;
			break;
		}
		system("cls");
	}

	std::cout << "\n-------------------\n";
	std::cout << "Thanks for playing!";
	std::cout << "\n-------------------\n\n\n";
	return 0;
}

void drawBoard()
{
	//Welcome Message

	std::cout << "-----------------------" << "\nWelcome to Tic-Tac-Toe! " << "\n-----------------------" << std::endl;
	std::cout << " ------------- ";
	for (int i = 0; i < 3; i++)
	{
		std::cout << std::endl;
		for (int j = 0; j < 3; j++)
		{
			std::cout << " | " << board[i][j];
		}
		std::cout << " | ";

	}
	std::cout << "\n ------------- ";
}

bool checkWin(char player)
{
	//Check rows
	for (int i = 0; i < 3; i++)
	{
		if (board[i][0] == player &&
			board[i][1] == player &&
			board[i][2] == player)
		{
			return true;
		}
	}

	//Check columns
	for (int i = 0; i < 3; i++)
	{
		if (board[0][i] == player &&
			board[1][i] == player &&
			board[2][i] == player)
		{
			return true;
		}
	}

	//Check diagonals
	if (board[0][0] == player && // Top left
		board[1][1] == player && // Middle
		board[2][2] == player)   // Bottom right
	{
		return true;
	}
	if (board[0][2] == player && // Bottom left
		board[1][1] == player && // Middle
		board[2][0] == player)   // Top right
	{
		return true;
	}

	return false;
}

bool checkDraw()
{
	// Check for free spots on the board
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (board[i][j] != 'X' && board[i][j] != 'O')
			{
				return false; //Empty spot found. It's not a draw.
			}
		}
	}
	return true; // Checked all spots and there are none empty. It's a draw!
}

void chooseSpot(char player)
{
	int choice;
	while (true)
	{
		std::cout << "\nPlayer " << player << ", choose a spot. (1-9)" << std::endl;
		std::cin >> choice;
		if (!std::cin.fail()) // Check if input is an integer
		{
			if (choice >= 1 && choice <= 9)
			{
				//Convert choice to an index for the board array.
				int row = (choice - 1) / 3;
				int column = (choice - 1) % 3;
				if (board[row][column] != 'O' && board[row][column] != 'X')
				{
					board[row][column] = player;
					break;
				}
				else
				{
					std::cout << "A player has already selected this spot." << std::endl;
				}
			}
			else
			{
				std::cout << "Choose a number between 1 and 9." << std::endl;
			}
		}
		else
		{
			std::cout << "Input a valid number." << std::endl;
		}
		//Validations failed, clear input stream and ask for input again.
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
}