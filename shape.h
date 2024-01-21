#pragma once
#include "point.h"
#include "board.h"

class Shape
{
private:
	char id;
	Point body[4];
public:
	void init(char id, Board& board);
	void move(Shape& s, Board& board);
	void rotateCounterClockwise(Shape& currentShape, Board& board);
	void rotateClockwise(Shape& currentShape, Board& board);
	void dropShape(const Shape& s, Board& board);
	bool hasReachedBottom(const Shape& s) const;
	bool hasReachedRightWall(const Shape& s) const;
	bool hasReachedLeftWall(const Shape& s) const;
	bool passedLeftWall(const Shape& s) const;
	bool passedRightWall(const Shape& s) const;
	bool passedUpperWall(const Shape& s) const;
	void correctLocationOfShape(const Shape& s);
	void drawShape(int left, int top);
	void eraseShape(int left, int top);
	void moveShapeToTheRight(Shape& s, GameConfig::eKeys direction, Board& board);
	void moveShapeToTheLeft(Shape& s, GameConfig::eKeys direction, Board& board);
	void moveShapeDown(const Shape& s, GameConfig::eKeys direction, Board& board);
	bool hasReachedToAnotherShape(const Shape& s, Board& board) const;
	bool collidedWithAnotherShape(const Shape& s, GameConfig::eKeys direction, Board& board) const;
	bool isGameOver(const Shape& s) const;
	bool isShapeOver(Shape& s, Board& board) const;
};
