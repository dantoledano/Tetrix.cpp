#pragma once
#include "gameConfig.h"


class Point
{
	int x;
	int y;
public:
	void initPoint(int x, int y);
	int getX() const { return this->x; }; // const beacause its a read-only function
	int getY() const { return this->y; }; // const beacause its a read-only function
	void setX(const int& _x) { x = _x; }  // const byRef is more efficient
	void setY(const int& _y) { y = _y; }  // const byRef is more efficient
	void draw(char ch);
	void movePoint(GameConfig::eKeys key);
};
