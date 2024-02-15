#pragma once
#include "gameConfig.h"
#include "board.h"
#include "point.h"

class Shape;

class Board
{
	const int xPos;
	int score;
	char matrix[GameConfig::GAME_HEIGHT][GameConfig::GAME_WIDTH];
	char keys[GameConfig::NUM_KEYS];

public:
	Board(int xPos, int score); //ctor - set xMIN of player, set score
	void setMatrixAt(size_t row, size_t col, char value);
	char getMatrixAt(size_t row, size_t col) const;
	int getScore() const { return this->score; }
	void setScore(const int& score_) { score = score_; }
	char getKeysAt(size_t index) const;
	void setKeys(char leftKey, char rightKey, char rotateKey, char crotateKey, char dropKey);
	int getLeft() const { return this->xPos; }
	void drawBorder() const;
	void eraseLine(int indexLine);
	bool isFullLine(int line) const;
	int clearFullLines();
	void DrawBoard();
	void DrawCubeInBoard(int x, int y, char ch);
	void resetBoard();
	bool explod(int activeX, int activeY);
	void organizeBoard();
	int evaluateScore(const Shape& s);
	void findBestMove(Shape& shape, int& chosenRotation, int& chosenPosition);
	int getHolesScore();
	void applyMove(Shape& shape, int rotation, int position);
	int checkLines(const Shape& s);
	int countGaps();
	int getHightOfBoard();
};
