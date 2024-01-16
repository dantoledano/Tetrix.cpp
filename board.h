#pragma once
#include "gameConfig.h"
#include "board.h"
#include "point.h"

class Board
{
	// private:
public:
	Point matrix[GameConfig::GAME_HEIGHT][GameConfig::GAME_WIDTH];
	Board(); //ctor
	//void removeFullLines();
	void eraseLine(int indexLine);
	bool isFullLine(int line);
	void clearFullLines();
	void DrawBoard();
	void DrawCubeInBoard(int x, int y, char ch);
	bool isGameOver() const;
};

