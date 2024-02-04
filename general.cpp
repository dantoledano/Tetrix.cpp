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
{ // clear the screen 
	system("cls");
}


char randomType() {  
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	int isTimeForBomb = std::rand() % 100;
	if (isTimeForBomb < 95) {
		// Array of characters
		char types[] = { 'L', 'J', 'O', 'I', 'S', 'Z', 'T' };
		// Calculate the number of characters in the array
		int numOfTypes = 7;
		// Generate a random index
		int randomIndex = std::rand() % numOfTypes;
		return types[randomIndex];
	}
	return GameConfig::BOMB;
}


void getKeyToContinue() {
	cout << "Press any key to continue...";
	while (true)
	{
		if (_kbhit())
		{
			_getch(); // clean the buffer
			return;
		}
	}
}
//char randomType() {  // הרנדום המקורי
//	std::srand(static_cast<unsigned int>(std::time(nullptr)));
//	// Array of characters
//	char types[] = { 'L', 'J', 'O', 'I', 'S', 'Z', 'T', '@'};
//	// Calculate the number of characters in the array
//	int numOfTypes = 8;
//	// Generate a random index
//	int randomIndex = std::rand() % numOfTypes;
//	return types[randomIndex];
//}


//char randomType() {  // רנדום לבדיקות
//	std::srand(static_cast<unsigned int>(std::time(nullptr)));
//	// Array of characters
//	//char types[] = { 'L', 'J', 'O', 'I', 'S', 'Z', 'T' };
//	char types[] = { 'L','T', '@' };
//	// Calculate the number of characters in the array
//	int numOfTypes = 3;
//	// Generate a random index
//	int randomIndex = std::rand() % numOfTypes;
//	return types[randomIndex];
//}

