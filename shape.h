#pragma once
#include "point.h"

	class Shape
	{
	private:
		char id;
		Point body[4];
		char sign;
public:
	void init(char id,char sign);
	void move(GameConfig::eKeys direction, Shape& s);
	void rotateCounterClockwise(Shape& currentShape);
	void rotateClockwise(Shape& currentShape);
	void dropShape(Shape& s);
	bool hasReachedBottom(const Shape& s);
};

