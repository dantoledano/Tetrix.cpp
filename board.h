#pragma once
#include "gameConfig.h"
#include "board.h"
#include "point.h"

class Board
{
	int xPos;
	//GameConfig::eKeys keys;
public:
	char keys[5];
	char matrix[GameConfig::GAME_HEIGHT][GameConfig::GAME_WIDTH];
	Board(int xPos); //ctor
	void setKeys(char leftKey, char rightKey, char rotateKey, char crotateKey, char dropKey);
	int getLeft() { return xPos; }
	void drawBorder();
	void eraseLine(int indexLine);
	bool isFullLine(int line) const;
	void clearFullLines();
	void DrawBoard();
	void DrawCubeInBoard(int x, int y, char ch);
};
