#include <conio.h> 
#include <iostream>
#include <Windows.h> 
#include "general.h"
#include "gameConfig.h"
#include "point.h"
//#include "shape_i.h"
#include "shape.h"

using namespace std;

// hi Alicia, this is a test 

void test();
void drawBorder();
char randomType();


int main()
{
	test();
	gotoxy(0, GameConfig::GAME_HEIGHT + GameConfig::MIN_Y + 2);
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

char randomType() { //GPT
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	// Array of characters
	char types[] = { 'L', 'J', 'O', 'I', 'S', 'Z', 'T'};
	// Calculate the number of characters in the array
	int numOfTypes = 7;
	// Generate a random index
	int randomIndex = std::rand() % numOfTypes;
	return types[randomIndex];
}



void test()
{
	drawBorder();
	Shape s;
	s.init('#', randomType());

	while (true)
	{
		int keyPressed = 'x';
		if (_kbhit())
		{
			keyPressed = _getch();
			if (keyPressed == (int)GameConfig::eKeys::ESC)
				break;
		}
	    s.move((GameConfig::eKeys)keyPressed,s);
		Sleep(500);
	}
}



