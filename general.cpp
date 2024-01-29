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


char randomType() {
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	// Array of characters
	//char types[] = { 'L', 'J', 'O', 'I', 'S', 'Z', 'T' };
	char types[] = { 'L', '@' };
	// Calculate the number of characters in the array
	int numOfTypes = 2;
	// Generate a random index
	int randomIndex = std::rand() % numOfTypes;
	return types[randomIndex];
}


//char randomType() {  // אל תמחק, לא בטוחה אם זה טוב אבל זה אמור לשמש אותנו להמשך
//	std::srand(static_cast<unsigned int>(std::time(nullptr)));
//	int isTimeForBomb = std::rand() % 100;
//	if (isTimeForBomb < 95) {
//		// Array of characters
//		char types[] = { 'L', 'J', 'O', 'I', 'S', 'Z', 'T' };
//		// Calculate the number of characters in the array
//		int numOfTypes = 7;
//		// Generate a random index
//		int randomIndex = std::rand() % numOfTypes;
//		return types[randomIndex];
//	}
//	return BOMB;
//}
