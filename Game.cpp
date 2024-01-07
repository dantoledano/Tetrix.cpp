// Game.cpp
#include "Game.h"


void Game::gotoxy(short x, short y) {
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}


void Game::drawBoard(int p) {
	for (int i = 0; i < boardHeight + 2; ++i) {
		for (int j = 0; j < boardWidth + 2; ++j) {
			gotoxy(p + j, 3 + i);
			if (i == 0) {
				cout << "_";
			}
			else if (i == boardHeight + 1) {
				cout << "-";
			}
			else if (j == 0 || j == boardWidth + 1) {
				cout << "|";
			}
			else {
				cout << " ";
			}
		}
	}
}




