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
