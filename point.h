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
	void draw(char ch);
	void movePoint(GameConfig::eKeys key);
};

