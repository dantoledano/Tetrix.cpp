#include "point.h"
#include "gameConfig.h"
#include "general.h"
#include "shape.h"
#include <iostream>
#include <Windows.h>
using namespace std;


void Point::initPoint(int x, int y)
{
	this->x = x;
	this->y = y;
}


void Point::draw(char ch, int left, int top)
{
	gotoxy(x + left - 1, y + top - 1);
	cout << ch;
}


void Point::movePoint(GameConfig::eKeys key)
{ // moving a single point in given direction (key).
	switch (key)
	{
	case GameConfig::eKeys::LEFT:
		x -= 1;
		break;
	case GameConfig::eKeys::RIGHT:
		x += 1;
		break;
	case GameConfig::eKeys::DOWN:
		y += 1;
		break;
	}
}
