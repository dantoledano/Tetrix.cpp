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
//	void move(GameConfig::eKeys direction, Shape& s, Board& board);
	void move(Shape& s, Board& board);
	void rotateCounterClockwise(Shape& currentShape, Board& board);
	void rotateClockwise(Shape& currentShape, Board& board);
	void dropShape(const Shape& s, Board& board);
	bool hasReachedBottom(const Shape& s);
	bool hasReachedRightWall(const Shape& s);
	bool hasReachedLeftWall(const Shape& s);
	bool passedLeftWall(const Shape& s);
	bool passedRightWall(const Shape& s);
	bool passedUpperWall(const Shape& s);
	void correctLocationOfShape(const Shape& s);
	void drawShape(int left, int top);
	void eraseShape(int left, int top);
	void moveShapeToTheRight(Shape& s, GameConfig::eKeys direction, Board& board);
	void moveShapeToTheLeft(Shape& s, GameConfig::eKeys direction, Board& board);
	void moveShapeDown(const Shape& s, GameConfig::eKeys direction, Board& board);
	bool hasReachedToAnotherShape(const Shape& s, Board& board);
	bool collidedWithAnotherShape(const Shape& s, GameConfig::eKeys direction, Board& board);
	bool isGameOver(const Shape& s) const;
	bool isShapeOver(Shape& s, Board& board);
	//bool play(Board& board);
	//int checkKeyPressed(int keyPressed, Shape& LeftShape, Shape& RightShape);
};

