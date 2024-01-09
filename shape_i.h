#pragma once
#include "Point.h"


class SHAPE_I
{
private:
	Point body[4];
	char ch;
public:
	void initI(char ch);
	void move(GameConfig::eKeys direction);
};

