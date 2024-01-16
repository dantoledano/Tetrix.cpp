#pragma once
#include "gameConfig.h"


class Point
{
	int x;
	int y;
	bool isActive = false;
public:
	void initPoint(int x, int y);
	int getX() const { return this->x; }; // const beacause its a read-only function
	int getY() const { return this->y; }; // const beacause its a read-only function
	bool getActive() const { return this->isActive; }
	void setX(const int& _x) { x = _x; }  // const byRef is more efficient
	void setY(const int& _y) { y = _y; }  // const byRef is more efficient
	void setActive(const bool& flag) { isActive = flag; }
	void draw(char ch);
	void movePoint(GameConfig::eKeys key);

};

