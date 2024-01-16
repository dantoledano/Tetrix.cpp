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
		this->id = 'I';
		break;
	case 'O':
		body[0].initPoint((GameConfig::GAME_WIDTH / 2), 1);
		body[1].initPoint((GameConfig::GAME_WIDTH / 2) + 1, 1);
		body[2].initPoint((GameConfig::GAME_WIDTH / 2), 2);
		body[3].initPoint((GameConfig::GAME_WIDTH / 2) + 1, 2);
		this->id = 'O';
		break;
	case 'S':
		body[0].initPoint((GameConfig::GAME_WIDTH / 2) + 1, 1);
		body[1].initPoint((GameConfig::GAME_WIDTH / 2), 1);
		body[2].initPoint((GameConfig::GAME_WIDTH / 2), 2);
		body[3].initPoint((GameConfig::GAME_WIDTH / 2) - 1, 2);
		this->id = 'S';
		break;
	case 'Z':
		body[0].initPoint((GameConfig::GAME_WIDTH / 2) - 1, 1);
		body[1].initPoint((GameConfig::GAME_WIDTH / 2), 1);
		body[2].initPoint((GameConfig::GAME_WIDTH / 2), 2);
		body[3].initPoint((GameConfig::GAME_WIDTH / 2) + 1, 2);
		this->id = 'Z';
		break;
	case 'T':
		body[0].initPoint((GameConfig::GAME_WIDTH / 2) - 1, 1);
		body[1].initPoint((GameConfig::GAME_WIDTH / 2), 1);
		body[2].initPoint((GameConfig::GAME_WIDTH / 2) + 1, 1);
		body[3].initPoint((GameConfig::GAME_WIDTH / 2), 2);
		this->id = 'T';
		break;
	case 'L':
		body[0].initPoint((GameConfig::GAME_WIDTH / 2), 1);
		body[1].initPoint((GameConfig::GAME_WIDTH / 2), 2);
		body[2].initPoint((GameConfig::GAME_WIDTH / 2), 3);
		body[3].initPoint((GameConfig::GAME_WIDTH / 2) + 1, 3);
		this->id = 'L';
		break;
	case 'J':
		body[0].initPoint((GameConfig::GAME_WIDTH / 2), 1);
		body[1].initPoint((GameConfig::GAME_WIDTH / 2), 2);
		body[2].initPoint((GameConfig::GAME_WIDTH / 2), 3);
		body[3].initPoint((GameConfig::GAME_WIDTH / 2) - 1, 3);
		this->id = 'J';
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


void Shape::move(GameConfig::eKeys direction, Shape& s, Board& board)
{
	eraseShape(s);
	switch (direction)
	{
	case GameConfig::eKeys::ROTATE:
		if (s.id == 'O') {
			moveShapeDown(s, GameConfig::eKeys::DOWN, board);
			break;
		}
		rotateClockwise(s, board);
		break;
	case GameConfig::eKeys::CROTATE:
		if (s.id == 'O') {
			moveShapeDown(s, GameConfig::eKeys::DOWN, board);
			break;
		}
		rotateCounterClockwise(s, board);
		break;
	case GameConfig::eKeys::DROP:
		dropShape(s, board);
		break;
	case GameConfig::eKeys::ESC:
		break;
	case GameConfig::eKeys::RIGHT:
		moveShapeToTheRight(s, direction, board);
		break;
	case GameConfig::eKeys::LEFT:
		moveShapeToTheLeft(s, direction, board);
		break;
	default:
		moveShapeDown(s, direction, board);
		break;
	}
	drawShape(s);  // re-drawing of the shape at new location
	if (hasReachedBottom(s) || hasReachedToAnotherShape(s, board))  // update matrix
	{
		for (int i = 0; i < 4; i++)
		{
			board.matrix[s.body[i].getY() - 1][s.body[i].getX() - 1] = '#'; // -1 beacuse min point is (1,1) and min cell in board is (0,0). also Y represents the rows and X represents the cols

		}
	}
}



bool Shape::collidedWithAnotherShape(const Shape& s, GameConfig::eKeys direction, Board& board)
{
	for (int i = 0; i < 4; i++)
	{
		if (board.matrix[s.body[i].getY()-1][s.body[i].getX()-1] == '#') 
		{
			return true;
		}
	}
	return false;
}


bool Shape::hasReachedToAnotherShape(const Shape& s, Board& board)
{
	for (int i = 0; i < 4; i++)  
	{
		if (board.matrix[s.body[i].getY()][s.body[i].getX() - 1] == '#')
			return true;
	}
	return false;
}


void Shape::moveShapeDown(const Shape& s, GameConfig::eKeys direction, Board& board)
{
	if (!hasReachedBottom(s) && !hasReachedToAnotherShape(s, board))
	{
		for (int i = 0; i < 4; i++)
		{
			body[i].movePoint(direction);
		}
	}
}


void Shape::moveShapeToTheLeft(Shape& s, GameConfig::eKeys direction, Board& board)
{
	Shape temp = s;
	for (int i = 0; i < 4; i++)
	{
		temp.body[i].movePoint(direction);
	}
	if (!hasReachedLeftWall(s) && !hasReachedToAnotherShape(s, board) && !collidedWithAnotherShape(temp, direction, board))
	{
		s = temp;
	}
	else {
		moveShapeDown(s, GameConfig::eKeys::DOWN, board);
	}
}


void Shape::moveShapeToTheRight(Shape& s, GameConfig::eKeys direction, Board& board)
{
	Shape temp = s;
	for (int i = 0; i < 4; i++)
	{
		temp.body[i].movePoint(direction);
	}
	if (!hasReachedRightWall(s) && !hasReachedToAnotherShape(s, board) && !collidedWithAnotherShape(temp, direction, board))
	{
		s = temp;
	}
	else {
		moveShapeDown(s, GameConfig::eKeys::DOWN, board);
	}

}


void Shape::rotateCounterClockwise(Shape& currentShape, Board& board) {
	Shape tempShape = currentShape;
	int pivotX = tempShape.body[1].getX();// Assuming the first cube is the center of the shape
	int pivotY = tempShape.body[1].getY();

	for (int i = 0; i < 4; ++i) {
		int relativeX = tempShape.body[i].getX() - pivotX;
		int relativeY = tempShape.body[i].getY() - pivotY;
		// Perform 90-degree counterclockwise rotation
		tempShape.body[i].setX(pivotX + relativeY);
		tempShape.body[i].setY(pivotY - relativeX);
	}
	bool collided = false;
	for (int i = 0; i < 4; i++)
	{
		if (board.matrix[tempShape.body[i].getY() - 1][tempShape.body[i].getX() - 1] == '#')
		{
			collided = true;
		}
	}
	if (!hasReachedToAnotherShape(tempShape, board) && !collided) {
		currentShape = tempShape;
	}
	correctLocationOfShape(currentShape);
}


void Shape::rotateClockwise(Shape& currentShape, Board& board) {
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
	bool collided = false;
	for (int i = 0; i < 4; i++)
	{
		if (board.matrix[tempShape.body[i].getY() - 1][tempShape.body[i].getX() - 1] == '#')
		{
			collided = true;
		}
	}
	if (!hasReachedToAnotherShape(tempShape, board) && !collided) {
		currentShape = tempShape;
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


void Shape::dropShape(const Shape& s, Board& board)
{
	// Drop the shape until it reaches the bottom of the game screen
	while (!hasReachedBottom(s) && !hasReachedToAnotherShape(s, board))
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

