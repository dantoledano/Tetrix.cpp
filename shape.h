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
	void move(GameConfig::eKeys direction, Shape& s, Board& board);
	void rotateCounterClockwise(Shape& currentShape, Board& board);
	void rotateClockwise(Shape& currentShape,Board& board);
	void dropShape(const Shape& s, Board& board);
	bool hasReachedBottom(const Shape& s);
	bool hasReachedRightWall(const Shape& s);
	bool hasReachedLeftWall(const Shape& s);
	bool passedLeftWall(const Shape& s);
	bool passedRightWall(const Shape& s);
	bool passedUpperWall(const Shape& s);
	void correctLocationOfShape(const Shape& s);
	void eraseShape(const Shape& s);
	void drawShape(const Shape& s);
	void moveShapeToTheRight(Shape& s, GameConfig::eKeys direction, Board& board);
	void moveShapeToTheLeft(Shape& s, GameConfig::eKeys direction, Board& board);
	void moveShapeDown(const Shape& s, GameConfig::eKeys direction);
	bool hasReachedToAnotherShape(const Shape& s, Board& board);
	//bool isRotationValid(const Shape& currentShape, Board& board);
};
