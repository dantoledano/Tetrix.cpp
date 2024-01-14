#include "shape.h"
#include "point.h"
#include "gameConfig.h"
#include <Windows.h>


void Shape::init(char id)
{
	switch (id) {
	case 'I':
		body[0].initPoint((GameConfig::GAME_WIDTH / 2) - 1, 1);
		body[1].initPoint((GameConfig::GAME_WIDTH / 2), 1);
		body[2].initPoint((GameConfig::GAME_WIDTH / 2) + 1, 1);
		body[3].initPoint((GameConfig::GAME_WIDTH / 2) + 2, 1);
		break;
	case 'O':
		body[0].initPoint((GameConfig::GAME_WIDTH / 2), 1);
		body[1].initPoint((GameConfig::GAME_WIDTH / 2) + 1, 1);
		body[2].initPoint((GameConfig::GAME_WIDTH / 2), 2);
		body[3].initPoint((GameConfig::GAME_WIDTH / 2) + 1, 2);
		break;
	case 'S':
		body[0].initPoint((GameConfig::GAME_WIDTH / 2) + 1, 1);
		body[1].initPoint((GameConfig::GAME_WIDTH / 2), 1);
		body[2].initPoint((GameConfig::GAME_WIDTH / 2), 2);
		body[3].initPoint((GameConfig::GAME_WIDTH / 2) - 1, 2);
		break;
	case 'Z':
		body[0].initPoint((GameConfig::GAME_WIDTH / 2) - 1, 1);
		body[1].initPoint((GameConfig::GAME_WIDTH / 2), 1);
		body[2].initPoint((GameConfig::GAME_WIDTH / 2), 2);
		body[3].initPoint((GameConfig::GAME_WIDTH / 2) + 1, 2);
		break;
	case 'T':
		body[0].initPoint((GameConfig::GAME_WIDTH / 2) - 1, 1);
		body[1].initPoint((GameConfig::GAME_WIDTH / 2), 1);
		body[2].initPoint((GameConfig::GAME_WIDTH / 2) + 1, 1);
		body[3].initPoint((GameConfig::GAME_WIDTH / 2), 2);
		break;
	case 'L':
		body[0].initPoint((GameConfig::GAME_WIDTH / 2), 1);
		body[1].initPoint((GameConfig::GAME_WIDTH / 2), 2);
		body[2].initPoint((GameConfig::GAME_WIDTH / 2), 3);
		body[3].initPoint((GameConfig::GAME_WIDTH / 2) + 1, 3);
		break;
	case 'J':
		body[0].initPoint((GameConfig::GAME_WIDTH / 2), 1);
		body[1].initPoint((GameConfig::GAME_WIDTH / 2), 2);
		body[2].initPoint((GameConfig::GAME_WIDTH / 2), 3);
		body[3].initPoint((GameConfig::GAME_WIDTH / 2) - 1, 3);
		break;
	}
	drawShape(*this);
}


void Shape::eraseShape(const Shape& s)
{
	for (int i = 0; i < 4; i++) {
		body[i].draw(' ');
	}
}


void Shape::drawShape(const Shape& s)
{
	for (int i = 0; i < 4; i++) {
		body[i].draw('#');
	}
}


void Shape::move(GameConfig::eKeys direction, const Shape& s)
{
	eraseShape(s);
	switch (direction)
	{
	case GameConfig::eKeys::ROTATE:
		rotateClockwise(s);
		break;
	case GameConfig::eKeys::CROTATE:
		rotateCounterClockwise(s);
		break;
	case GameConfig::eKeys::DROP: 
		dropShape(s);
		break;
	case GameConfig::eKeys::ESC:
		break;
	case GameConfig::eKeys::RIGHT:
		moveShapeToTheRight(s, direction);
		break;
	case GameConfig::eKeys::LEFT:
		moveShapeToTheLeft(s, direction);
		break;
	default:
		moveShapeDown(s, direction);
		break;
	}
	drawShape(s);  // re-drawing of the shape at new location
}


void Shape::moveShapeDown(const Shape& s, GameConfig::eKeys direction)
{
	if (!hasReachedBottom(s))
	{
		for (int i = 0; i < 4; i++)
		{
			body[i].movePoint(direction);
		}
	}
}


void Shape::moveShapeToTheLeft(const Shape& s, GameConfig::eKeys direction)
{
	if (!hasReachedLeftWall(s))
	{
		for (int i = 0; i < 4; i++)
		{
			body[i].movePoint(direction);
		}
	}
	else {
		if (!hasReachedBottom(s))
		{
			for (int i = 0; i < 4; i++)
			{
				body[i].movePoint(GameConfig::eKeys::DOWN);
			}
		}
	}
}


void Shape::moveShapeToTheRight(const Shape& s, GameConfig::eKeys direction)
{
	if (!hasReachedRightWall(s))
	{
		for (int i = 0; i < 4; i++)
		{
			body[i].movePoint(direction);
		}
	}
	else {
		if (!hasReachedBottom(s))
		{
			for (int i = 0; i < 4; i++)
			{
				body[i].movePoint(GameConfig::eKeys::DOWN);
			}
		}
	}
}


void Shape::rotateCounterClockwise(const Shape& currentShape) {
	int pivotX = body[1].getX();        // Assuming the first cube is the center of the shape
	int pivotY = body[1].getY();

	for (int i = 0; i < 4; ++i) {
		int relativeX = body[i].getX() - pivotX;
		int relativeY = body[i].getY() - pivotY;
		// Perform 90-degree clockwise rotation
		body[i].setX(pivotX + relativeY);
		body[i].setY(pivotY - relativeX);
	}

	correctLocationOfShape(currentShape);
}


void Shape::rotateClockwise(const Shape& currentShape) {
	int pivotX = body[1].getX();// Assuming the first cube is the center of the shape
	int pivotY = body[1].getY();

	for (int i = 0; i < 4; ++i) {
		int relativeX = body[i].getX() - pivotX;
		int relativeY = body[i].getY() - pivotY;
		// Perform 90-degree counterclockwise rotation
		body[i].setX(pivotX - relativeY);
		body[i].setY(pivotY + relativeX);
	}

	correctLocationOfShape(currentShape);
}


void Shape::correctLocationOfShape(const Shape& s)
{
	while (passedRightWall(s))
	{
		for (int i = 0; i < 4; i++)
		{
			body[i].movePoint(GameConfig::eKeys::LEFT);
		}
	}
	while (passedLeftWall(s))
	{
		for (int i = 0; i < 4; i++)
		{
			body[i].movePoint(GameConfig::eKeys::RIGHT);
		}
	}
	while (passedUpperWall(s))
	{
		for (int i = 0; i < 4; i++)
		{
			body[i].movePoint(GameConfig::eKeys::DOWN);
		}
	}
}


bool Shape::passedUpperWall(const Shape& s)
{
	for (int i = 0; i < 4; i++)
	{
		if (body[i].getY() < 1)
			return true;
	}
	return false;
}


bool Shape::passedRightWall(const Shape& s)
{
	for (int i = 0; i < 4; i++)
	{
		if (body[i].getX() > GameConfig::GAME_WIDTH)
			return true;
	}
	return false;
}


bool Shape::passedLeftWall(const Shape& s)
{
	for (int i = 0; i < 4; i++)
	{
		if (body[i].getX() < 1)
			return true;
	}
	return false;
}


void Shape::dropShape(const Shape& s)
{
	// Drop the shape until it reaches the bottom of the game screen
	while (!hasReachedBottom(s))
	{
		for (int i = 0; i < 4; i++)
		{
			body[i].draw(' ');
			body[i].movePoint(GameConfig::eKeys::DOWN);
		}
		for (int i = 0; i < 4; i++)
			body[i].draw('#');
		Sleep(50);
	}
}


bool Shape::hasReachedBottom(const Shape& s)
{
	// Check if any part of the shape has reached the bottom of the game screen
	for (int i = 0; i < 4; i++)
	{
		if (body[i].getY() == GameConfig::GAME_HEIGHT)
			return true;
	}
	return false;
}


bool Shape::hasReachedRightWall(const Shape& s)
{
	for (int i = 0; i < 4; i++)
	{
		if (body[i].getX() >= GameConfig::GAME_WIDTH)
			return true;
	}
	return false;
}


bool Shape::hasReachedLeftWall(const Shape& s)
{
	for (int i = 0; i < 4; i++)
	{
		if (body[i].getX() <= 1)
			return true;
	}
	return false;
}

