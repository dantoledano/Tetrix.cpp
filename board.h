#pragma once
#include "gameConfig.h"
#include "board.h"
#include "point.h"

class Board
{
	int xPos;
	int score;
public:
	Board(int xPos, int score); //ctor - set xMIN of player, set score
	char keys[5];
	char matrix[GameConfig::GAME_HEIGHT][GameConfig::GAME_WIDTH];
	int getScore() const { return this->score; }
	void setScore(const int& score_) { score = score_; }
	void setKeys(char leftKey, char rightKey, char rotateKey, char crotateKey, char dropKey);
	int getLeft() { return xPos; }
	void drawBorder() const;
	void eraseLine(int indexLine);
	bool isFullLine(int line) const;
	int clearFullLines();
	void DrawBoard();
	void DrawCubeInBoard(int x, int y, char ch);
	void resetBoard();
};
