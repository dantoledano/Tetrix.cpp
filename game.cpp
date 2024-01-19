#include "game.h"


//Game::Game()
//{
//	board1.setKeys('a', 'd', 's', 'w', 'x');
//	board2.setKeys('j', 'l', 'k', 'i', 'm');
//}


void Game::run()
{
	board1.drawBorder();
	board2.drawBorder();
	Shape s1;
	Shape s2;
	bool isGameOver = false;
	while (!isGameOver)
	{
		s1.init(randomType(), board1);
		s2.init(randomType(), board2);
		while (!s1.hasReachedBottom(s1) && !s1.hasReachedToAnotherShape(s1, board1))
		{
			Sleep(500);
			int keyPressed = 'z'; // down
			if (_kbhit())
			{
				keyPressed = _getch();
				if (keyPressed == (int)GameConfig::eKeys::ESC)
					break;
			}
			s1.move((GameConfig::eKeys)keyPressed, s1, board1);
			s2.move((GameConfig::eKeys)keyPressed, s2, board2);
		}
		isGameOver = s1.isGameOver(s1);
	}
}
