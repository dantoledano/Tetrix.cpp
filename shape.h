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
	void move(Board& board);
	void rotateCounterClockwise(Board& board);
	void rotateClockwise(Board& board);
	void dropShape(Board& board);
	bool hasReachedBottom() const;
	bool hasReachedRightWall() const;
	bool hasReachedLeftWall() const;
	bool passedLeftWall() const;
	bool passedRightWall() const;
	bool passedUpperWall() const;
	void correctLocationOfShape();
	void drawShape(int left, int top);
	void eraseShape(int left, int top);
	void moveShapeToTheRight(Board& board);
	void moveShapeToTheLeft(Board& board);
	void moveShapeDown(Board& board);
	bool hasReachedToAnotherShape(Board& board) const;
	bool collidedWithAnotherShape(Board& board) const;
	bool isGameOver() const;
	bool isShapeOver(Board& board) const;
};
