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
	gotoxy(x+left-1 , y+top-1);
	cout << ch;
}


void Point::movePoint(GameConfig::eKeys key)
{
	switch (key)
	{
	case GameConfig::eKeys::LEFT:
	case GameConfig::eKeys::LEFT_CAP:
		x -= 1;
		break;
	case GameConfig::eKeys::RIGHT:
	case GameConfig::eKeys::RIGHT_CAP:
		x += 1;
		break;
	case GameConfig::eKeys::DOWN:
		y += 1;
		break;
	}
}
