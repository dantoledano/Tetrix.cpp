#pragma once
#include "gameConfig.h"


class Point
{
	int x;
	int y;
	int diff_x;
	int diff_y;

public:
	void initPoint(int x, int y);
	int getX() { return this->x; };
	int getY() { return this->y; };
	void setX(int _x) { x = _x; }
	void setY(int _y) { y = _y; }
	void draw(char ch);
	void movePoint(GameConfig::eKeys key);
};

