#include "general.h"
#include <windows.h> // for gotoxy
#include <process.h> // for system
#include <iostream>
#include "gameConfig.h"
using namespace std;


void gotoxy(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	cout.flush();
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}


void clrscr()
{
	system("cls");
}


void drawBorder()
{
	for (int col = GameConfig::MIN_X; col < GameConfig::GAME_WIDTH + GameConfig::MIN_X; col++)
	{
		gotoxy(col, GameConfig::MIN_Y - 1);
		cout << "-";

		gotoxy(col, GameConfig::GAME_HEIGHT + GameConfig::MIN_Y);
		cout << "-";
	}

	for (int row = GameConfig::MIN_Y - 1; row <= GameConfig::GAME_HEIGHT + GameConfig::MIN_Y; row++)
	{
		gotoxy(GameConfig::MIN_X - 1, row);
		cout << "|";

		gotoxy(GameConfig::GAME_WIDTH + GameConfig::MIN_X, row);
		cout << "|";
	}
}



char randomType() { 
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	// Array of characters
	char types[] = { 'L', 'J', 'O', 'I', 'S', 'Z', 'T' };
	// Calculate the number of characters in the array
	int numOfTypes = 7;
	// Generate a random index
	int randomIndex = std::rand() % numOfTypes;
	return types[randomIndex];
}