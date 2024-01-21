#pragma once
#include "gameConfig.h"
#include "board.h"
#include "point.h"

class Board
{
	int xPos;
public:
	Board(int xPos); //ctor - set xPos of player
	char keys[5];
	char matrix[GameConfig::GAME_HEIGHT][GameConfig::GAME_WIDTH];
	void setKeys(char leftKey, char rightKey, char rotateKey, char crotateKey, char dropKey);
	int getLeft() { return xPos; }
	void drawBorder();
	void eraseLine(int indexLine);
	bool isFullLine(int line) const;
	void clearFullLines();
	void DrawBoard();
	void DrawCubeInBoard(int x, int y, char ch);
	void resetBoard();
};
