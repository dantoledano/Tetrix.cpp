#include "general.h"
using namespace std;


void test();


int main()
{
	test();
	gotoxy(0, GameConfig::GAME_HEIGHT + GameConfig::MIN_Y + 2);
}


void test()
{
	Board b1;
	drawBorder();
	Shape s;
	while (true)
	{
		s.init(randomType());
		while (!s.hasReachedBottom(s) && !s.hasReachedToAnotherShape(s,b1))
		{
			Sleep(700);
			int keyPressed = 'z'; // down
			if (_kbhit())
			{
				keyPressed = _getch();
				if (keyPressed == (int)GameConfig::eKeys::ESC)
					break;
			}
			s.move((GameConfig::eKeys)keyPressed, s, b1);
		}

	}
}


