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


void Point::draw(char ch)
{
	gotoxy(x + GameConfig::MIN_X - 1, y + GameConfig::MIN_Y - 1);
	cout << ch;
}


void Point::movePoint(GameConfig::eKeys key)
{
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