#include "shape.h"
#include "point.h"
#include "gameConfig.h"
#include <Windows.h>
#include "board.h"


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
		this->id='O';
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
			moveShapeDown(s, GameConfig::eKeys::DOWN);
			break;
		}
		rotateClockwise(s,board);
		break;
	case GameConfig::eKeys::CROTATE:
		if (s.id == 'O') {
			moveShapeDown(s, GameConfig::eKeys::DOWN);
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
		moveShapeToTheLeft(s, direction,board);
		break;
	default:
		moveShapeDown(s, direction);
		break;
	}
	drawShape(s);  // re-drawing of the shape at new location
	if (hasReachedBottom(s) || hasReachedToAnotherShape(s, board))
	{
		for (int i = 0; i < 4; i++)
		{
			board.matrix[s.body[i].getY() - 1][s.body[i].getX() - 1] = '#'; // -1 beacuse min point is (1,1) and min cell in board is (0,0). also Y represents the rows and X represents the cols
		}
	}
}


bool Shape::hasReachedToAnotherShape(const Shape& s, Board& board)
{
	for (int i = 0; i < 4; i++)  // search at any low point if its right above some other shape
	{
		if (board.matrix[s.body[i].getY()][s.body[i].getX() - 1] == '#')
			return true;
	}
	return false;
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


void Shape::moveShapeToTheLeft(Shape& s, GameConfig::eKeys direction, Board& board)
{
	Shape temp = s;
	for (int i = 0; i < 4; i++)
	{
		temp.body[i].movePoint(direction);
	}
	if (!hasReachedLeftWall(temp) && !hasReachedToAnotherShape(temp, board))
	{
		s = temp;
	}
	else {
		moveShapeDown(s, GameConfig::eKeys::DOWN);
	}
}


void Shape::moveShapeToTheRight(Shape& s, GameConfig::eKeys direction, Board& board)
{
	Shape temp = s;
	for (int i = 0; i < 4; i++)
	{
		temp.body[i].movePoint(direction);
	}
	if (!hasReachedRightWall(temp) && !hasReachedToAnotherShape(temp,board))
	{
		s = temp;
	}
	else {
		moveShapeDown(s, GameConfig::eKeys::DOWN);
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
	if (!hasReachedToAnotherShape(tempShape, board)) {
		currentShape = tempShape;
	}
	correctLocationOfShape(currentShape);
}


//void Shape::rotateClockwise(const Shape& currentShape, Board& board) {
//	int pivotX = body[1].getX();// Assuming the first cube is the center of the shape
//	int pivotY = body[1].getY();
//
//	for (int i = 0; i < 4; ++i) {
//		int relativeX = body[i].getX() - pivotX;
//		int relativeY = body[i].getY() - pivotY;
//		// Perform 90-degree counterclockwise rotation
//		body[i].setX(pivotX - relativeY);
//		body[i].setY(pivotY + relativeX);
//	}
//	if(!isRotationValid(currentShape,?, true))
//	correctLocationOfShape(currentShape);
//}


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
	if (!hasReachedToAnotherShape(tempShape, board)) {
		currentShape = tempShape;
	}
	correctLocationOfShape(currentShape);
}

//void Shape::rotateClockwise(const Shape& currentShape, Board& board) {
//	int pivotX = body[1].getX();  // Assuming the first cube is the center of the shape
//	int pivotY = body[1].getY();
//	int newX, newY;
//
//	// Perform the rotation on the temporary shape
//	for (int i = 0; i < 4; ++i) {
//		int relativeX = body[i].getX() - pivotX;
//		int relativeY = body[i].getY() - pivotY;
//		// Perform 90-degree clockwise rotation
//		body[i].setX(pivotX + relativeY);
//		body[i].setY(pivotY - relativeX);
//	    newX = body[i].getX();
//	    newY = body[i].getY();
//	}
//
//	// Check if the clockwise rotation is valid
//	for (int i = 0; i < 4; i++) {
//		
//		// Check if the new position is within the board boundaries
//		if (newX < 1 || newX > GameConfig::GAME_WIDTH || newY < 1 || newY > GameConfig::GAME_HEIGHT) {
//			// If the new position is out of bounds, correct the location and exit
//			correctLocationOfShape(currentShape);
//			return;
//		}
//
//		// Check if the new position collides with an existing shape on the board
//		if (board.isOccupied(newX, newY)) {
//			// If collision, correct the location and exit
//			correctLocationOfShape(currentShape);
//			return;
//		}
//	}
//}


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
