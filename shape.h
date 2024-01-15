#pragma once
#include "point.h"
#include "board.h"

class Shape
{
private:
	char id;
	Point body[4];
public:
	void init(char id);
	void move(GameConfig::eKeys direction, const Shape& s, Board& board);
	void rotateCounterClockwise(const Shape& currentShape);
	void rotateClockwise(const Shape& currentShape);
	void dropShape(const Shape& s);
	bool hasReachedBottom(const Shape& s);
	bool hasReachedRightWall(const Shape& s);
	bool hasReachedLeftWall(const Shape& s);
	bool passedLeftWall(const Shape& s);
	bool passedRightWall(const Shape& s);
	bool passedUpperWall(const Shape& s);
	void correctLocationOfShape(const Shape& s);
	void eraseShape(const Shape& s);
	void drawShape(const Shape& s);
	void moveShapeToTheRight(const Shape& s, GameConfig::eKeys direction);
	void moveShapeToTheLeft(const Shape& s, GameConfig::eKeys direction);
	void moveShapeDown(const Shape& s, GameConfig::eKeys direction);
};
