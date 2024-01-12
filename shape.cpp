#include "shape.h"
#include "point.h"
#include "gameConfig.h"
#include <Windows.h>

void Shape::init(char sign, char id)
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
	// initializing coordinates of shape I
	// printing shape I
	for (int i = 0; i < 4; i++)
	{
		body[i].draw(sign);
	}
}

void Shape::move(GameConfig::eKeys direction, Shape& s)
{
	for (int i = 0; i < 4; i++) {
		body[i].draw(' ');
	}
	switch (direction)
	{
	case GameConfig::eKeys::ROTATE:
		rotateClockwise(s);
		break;
	case GameConfig::eKeys::CROTATE:
		rotateCounterClockwise(s);
		break;
	case GameConfig::eKeys::DROP:  // Added case for dropping the shape
		dropShape(s);
		break;
	case GameConfig::eKeys::ESC:
		break;
	default:
		for (int i = 0; i < 4; i++)
		{
			// earasing the shape and then moving all coordinates in given direction
			body[i].movePoint(direction);
		}
		break;
	}
	// re-drawing of the shape
	for (int i = 0; i < 4; i++)
		body[i].draw('#');
}

//void Shape::move(GameConfig::eKeys direction, Shape& s) // משאיר לבנתיים עוד פונ' שעובדת
//{
//	for (int i = 0; i < 4; i++)
//	{
//		// earasing the shape and then moving all coordinates in given direction
//		body[i].draw(' ');
//		if (direction != (GameConfig::eKeys::CROTATE) && direction != (GameConfig::eKeys::ROTATE)) {
//			body[i].movePoint(direction);
//		}
//	}
//	if (direction == (GameConfig::eKeys::ROTATE)){
//		rotateClockwise(s);
//	}
//	if (direction == (GameConfig::eKeys::CROTATE)) {
//		rotateCounterClockwise(s);
//	}
//	// re-drawing of the shape
//	for (int i = 0; i < 4; i++)
//	{
//		body[i].draw('#');
//	}
//}

void Shape::rotateCounterClockwise(Shape& currentShape) {
	Shape tempShape = currentShape;
	int pivotX = tempShape.body[1].getX();                                   // Assuming the first cube is the center of the shape
	int pivotY = tempShape.body[1].getY();

	for (int i = 0; i < 4; ++i) {
		int relativeX = tempShape.body[i].getX() - pivotX;
		int relativeY = tempShape.body[i].getY() - pivotY;
		// Perform 90-degree clockwise rotation
		tempShape.body[i].setX(pivotX + relativeY);
		tempShape.body[i].setY(pivotY - relativeX);
	}
	/*if (isMoveValid(tempShape)) {// צריכים לממש
		currentShape = tempShape;
	}*/
	currentShape = tempShape;
}

void Shape::rotateClockwise(Shape& currentShape) {
	Shape tempShape = currentShape;
	int pivotX = tempShape.body[1].getX();// Assuming the first cube is the center of the shape
	int pivotY = tempShape.body[1].getY();

	for (int i = 0; i < 4; ++i) {
		int relativeX = tempShape.body[i].getX() - pivotX;
		int relativeY = tempShape.body[i].getY() - pivotY;
		// Perform 90-degree counterclockwise rotation
		tempShape.body[i].setX(pivotX - relativeY);
		tempShape.body[i].setY(pivotY + relativeX);
	}
	/*if (isMoveValid(tempShape)) {
		currentShape = tempShape;
	}*/
	currentShape = tempShape;
}

void Shape::dropShape(Shape& s)
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
