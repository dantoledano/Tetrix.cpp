#pragma once
#include "gameConfig.h"


class Point
{
	int x;
	int y;
public:
	void initPoint(int x, int y);
	void draw(char ch, int left, int top);
	int getX() const { return this->x; }; 
	int getY() const { return this->y; }; 
	void setX(const int& _x) { x = _x; } 
	void setY(const int& _y) { y = _y; }  
	void movePoint(GameConfig::eKeys key);

};
