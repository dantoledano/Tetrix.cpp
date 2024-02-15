#pragma once
#include "point.h"
#include "board.h"

class Shape
{
private:
	char id;
	Point body[4];
	bool hasExploded = false;
public:
	static constexpr int NUM_CUBES = 4;
	Point getBodyAt(int index) const { return this->body[index]; }
	char getId() const { return this->id; }
	int getHasExploded() const { return this->hasExploded; }
	void setHasExploded(bool hasExploded) { this->hasExploded = hasExploded; }
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
	bool passedLowerWall() const;
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
	int  getSumOfHeights() const;
	int getFirstX() const;
	char getID() { return id; }
	int getHeightOfCube(int i) const;
	void updateMatrix(Board& b, bool add);
};
