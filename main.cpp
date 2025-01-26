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
#include <chrono>
#include <thread>


#pragma region Declare Functions
void drawBoard();
bool checkWin(char player);
bool checkDraw();
void chooseSpot(char player);
void dumbAI(char player);
#pragma endregion

#pragma region Declare & Initialize Global Variables
//Player Symbols
const char player1 = 'X';
const char player2 = 'O';

//Create 2D array for the board
char board[3][3]
{
	{'1', '2', '3'},
	{'4', '5', '6'},
	{'7', '8', '9'}
};
#pragma endregion

#pragma region Main Game Loop
int main()
{
	//Game Loop
	while (true)
	{
		//Draw the board.
		drawBoard();

		//Player 1's turn
		chooseSpot(player1); // Get Player 1's input.
		if (checkWin(player1)) // Check if there was a win
		{
			//Clear the screen, draw the board again, output a winning message and break out of the game loop.
			system("cls");
			drawBoard();
			std::cout << "\nPlayer " << player1 << " Wins! Congrats!" << std::endl;
			break;
		}
		if (checkDraw()) // Check if there was a draw
		{
			//Clear the screen, draw the board again, output a draw message and break out of the game loop.
			system("cls");
			drawBoard();
			std::cout << "\nIt's a draw!" << std::endl;
			break;
		}

		//End of player 1's turn. Clear the screen and redraw the board.
		system("cls");
		drawBoard();

		//Player 2's turn
		dumbAI(player2); // Get AI's input.
		//chooseSpot(player2); // Get Player 2's input
		if (checkWin(player2)) // Check if there was a win
		{
			//Clear the screen, draw the board again, output a winning message and break out of the game loop.
			system("cls");
			drawBoard();
			std::cout << "\nPlayer " << player2 << " Wins! Congrats!" << std::endl;
			break;
		}
		if (checkDraw()) // Check if there was a draw
		{
			//Clear the screen, draw the board again, output a draw message and break out of the game loop.
			system("cls");
			drawBoard();
			std::cout << "\nIt's a draw!" << std::endl;
			break;
		}

		//End of player 2's turn. Clear the screen.
		system("cls");
	}

	//Output an end of game message.
	std::cout << "\n-------------------\n";
	std::cout << "Thanks for playing!";
	std::cout << "\n-------------------\n\n\n";
	system("pause"); //Suspend processing so the player can read the game results.
	return 0;
}
#pragma endregion

#pragma region Define Functions
void drawBoard()
{
	//Welcome Message
	std::cout << "-----------------------" << "\nWelcome to Tic-Tac-Toe! " << "\n-----------------------" << std::endl;

	//Loop through the board 2D array and print it to the screen, with some spacers.
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
	while (true) //Input validation loop
	{
		std::cout << "\nPlayer " << player << ", choose a spot. (1-9)" << std::endl; //Output a prompt for the player to input a number.
		std::cin >> choice; //Get the players input.
		if (!std::cin.fail()) // Check if input is an integer
		{
			if (choice >= 1 && choice <= 9) //Check if the input is within the desired range.
			{
				//Convert input to an index for the board array.
				int row = (choice - 1) / 3;
				int column = (choice - 1) % 3;
				if (board[row][column] != 'O' && board[row][column] != 'X') //Check if the chosen spot is already taken.
				{
					board[row][column] = player; //Set the spot on the board to the players symbol and break out of the input validation loop.
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
		//Validations failed, clear input stream.
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
}

void dumbAI(char player)
{
	srand(time(NULL)); // Initialise random seed
	std::cout << "\nAI is thinking..." << std::endl; // Display message

	while (true)
	{
		//Pick random number between 1 and 9.
		int choice = rand() % 9 + 1;
		//Convert input to an index for the board array.
		int row = (choice - 1) / 3;
		int column = (choice - 1) % 3;

		//Check if the chosen spot is already taken.
		if (board[row][column] != 'O' && board[row][column] != 'X') 
		{
			std::this_thread::sleep_for(std::chrono::seconds(2)); // Sleep for a few seconds to fake thinking time.
			board[row][column] = player; //Set the spot on the board to the AI players symbol.
			break; //Choice has been made, break out of the input validation loop.
		}
	}
}

#pragma endregion