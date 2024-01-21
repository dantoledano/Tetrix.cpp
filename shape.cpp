#include "shape.h"
#include "point.h"
#include "gameConfig.h"
#include <windows.h>
#include "general.h"

const int NUM_CUBES = 4;

void Shape::init(char id, Board& board)
{
	this->id = id;
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
	drawShape(board.getLeft(), GameConfig::MIN_Y);
}


bool Shape::isShapeOver(Shape& s, Board& board) const {
	return (s.hasReachedBottom(s) || s.hasReachedToAnotherShape(s, board));
}


void Shape::eraseShape(int left, int top)
{
	for (int i = 0; i < NUM_CUBES; i++) {
		body[i].draw(' ', left, top);
	}
}


void Shape::drawShape(int left, int top)
{
	for (int i = 0; i < NUM_CUBES; i++) {
		body[i].draw('#', left, top);
	}
}


void Shape::move(Shape& s, Board& board) { //int direction,
	int activeX, activeY;
	int completedLine = 0;
	drawShape(board.getLeft(), GameConfig::MIN_Y);  // re-drawing of the shape at new location
	if (hasReachedBottom(s) || hasReachedToAnotherShape(s, board))  // update matrix
	{
		eraseShape(board.getLeft(), GameConfig::MIN_Y);
		for (int i = 0; i < NUM_CUBES; i++)
		{
			activeX = s.body[i].getX();
			activeY = s.body[i].getY();
			board.matrix[activeY - 1][activeX - 1] = '#';
		}
		board.DrawBoard();
		completedLine = board.clearFullLines();
		board.setScore(board.getScore() + (completedLine * 100));
		if (completedLine > 1)
			board.setScore(board.getScore() + (completedLine * 50)); //for combos
	}
}



bool Shape::collidedWithAnotherShape(const Shape& s, Board& board) const
{
	for (int i = 0; i < NUM_CUBES; i++)
	{
		if (board.matrix[s.body[i].getY() - 1][s.body[i].getX() - 1] == '#')
		{
			return true;
		}
	}
	return false;
}


bool Shape::hasReachedToAnotherShape(const Shape& s, Board& board) const
{
	for (int i = 0; i < NUM_CUBES; i++)
	{
		if (board.matrix[s.body[i].getY()][s.body[i].getX() - 1] == '#')
			return true;
	}
	return false;
}


void Shape::moveShapeDown(const Shape& s, Board& board)
{
	if (!hasReachedBottom(s) && !hasReachedToAnotherShape(s, board))
	{
		for (int i = 0; i < NUM_CUBES; i++)
		{
			body[i].movePoint(GameConfig::eKeys::DOWN);
		}
	}
}


void Shape::moveShapeToTheLeft(Shape& s, Board& board)
{
	Shape temp = s;
	for (int i = 0; i < NUM_CUBES; i++)
	{
		temp.body[i].movePoint(GameConfig::eKeys::LEFT);
	}
	if (!hasReachedLeftWall(s) && !hasReachedToAnotherShape(s, board) && !collidedWithAnotherShape(temp, board))
	{
		s = temp;
	}
	else {
		moveShapeDown(s, board);
	}
}


void Shape::moveShapeToTheRight(Shape& s, Board& board)
{
	Shape temp = s;
	for (int i = 0; i < NUM_CUBES; i++)
	{
		temp.body[i].movePoint(GameConfig::eKeys::RIGHT);
	}
	if (!hasReachedRightWall(s) && !hasReachedToAnotherShape(s, board) && !collidedWithAnotherShape(temp, board))
	{
		s = temp;
	}
	else {
		moveShapeDown(s, board);
	}

}


void Shape::rotateCounterClockwise(Shape& currentShape, Board& board) {
	if (currentShape.id == 'O') {
		moveShapeDown(currentShape, board);
		return;
	}
	Shape tempShape = currentShape;
	int pivotX = tempShape.body[1].getX();// Assuming the first cube is the center of the shape
	int pivotY = tempShape.body[1].getY();

	for (int i = 0; i < NUM_CUBES; ++i) {
		int relativeX = tempShape.body[i].getX() - pivotX;
		int relativeY = tempShape.body[i].getY() - pivotY;
		// Perform 90-degree counterclockwise rotation
		tempShape.body[i].setX(pivotX + relativeY);
		tempShape.body[i].setY(pivotY - relativeX);
	}
	bool collided = false;
	for (int i = 0; i < NUM_CUBES; i++)
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
	if (currentShape.id == 'O') {
		moveShapeDown(currentShape, board);
		return;
	}
	Shape tempShape = currentShape;
	int pivotX = tempShape.body[1].getX();// Assuming the first cube is the center of the shape
	int pivotY = tempShape.body[1].getY();

	for (int i = 0; i < NUM_CUBES; ++i) {
		int relativeX = tempShape.body[i].getX() - pivotX;
		int relativeY = tempShape.body[i].getY() - pivotY;
		// Perform 90-degree counterclockwise rotation
		tempShape.body[i].setX(pivotX - relativeY);
		tempShape.body[i].setY(pivotY + relativeX);
	}
	bool collided = false;
	for (int i = 0; i < NUM_CUBES; i++)
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
		for (int i = 0; i < NUM_CUBES; i++)
		{
			body[i].movePoint(GameConfig::eKeys::LEFT);
		}
	}
	while (passedLeftWall(s))
	{
		for (int i = 0; i < NUM_CUBES; i++)
		{
			body[i].movePoint(GameConfig::eKeys::RIGHT);
		}
	}
	while (passedUpperWall(s))
	{
		for (int i = 0; i < NUM_CUBES; i++)
		{
			body[i].movePoint(GameConfig::eKeys::DOWN);
		}
	}
}


bool Shape::passedUpperWall(const Shape& s) const
{
	for (int i = 0; i < NUM_CUBES; i++)
	{
		if (body[i].getY() < 1)
			return true;
	}
	return false;
}


bool Shape::passedRightWall(const Shape& s) const
{
	for (int i = 0; i < NUM_CUBES; i++)
	{
		if (body[i].getX() > GameConfig::GAME_WIDTH)
			return true;
	}
	return false;
}


bool Shape::passedLeftWall(const Shape& s) const
{
	for (int i = 0; i < NUM_CUBES; i++)
	{
		if (body[i].getX() < 1)
			return true;
	}
	return false;
}


void Shape::dropShape(const Shape& s, Board& board)
{
	while (!hasReachedBottom(*this) && !hasReachedToAnotherShape(*this, board)) {
		// Erase the shape from the current position
		eraseShape(board.getLeft(), GameConfig::MIN_Y);
		// Move the shape down
		for (int i = 0; i < NUM_CUBES; i++) {
			body[i].movePoint(GameConfig::eKeys::DOWN);
		}
		// Draw the shape at the new position
		drawShape(board.getLeft(), GameConfig::MIN_Y);
	}
}


bool Shape::hasReachedBottom(const Shape& s) const
{
	// Check if any part of the shape has reached the bottom of the game screen
	for (int i = 0; i < NUM_CUBES; i++)
	{
		if (body[i].getY() == GameConfig::GAME_HEIGHT)
			return true;
	}
	return false;
}


bool Shape::hasReachedRightWall(const Shape& s) const
{
	for (int i = 0; i < NUM_CUBES; i++)
	{
		if (body[i].getX() >= GameConfig::GAME_WIDTH)
			return true;
	}
	return false;
}


bool Shape::hasReachedLeftWall(const Shape& s) const
{
	for (int i = 0; i < NUM_CUBES; i++)
	{
		if (body[i].getX() <= 1)
			return true;
	}
	return false;
}


bool Shape::isGameOver(const Shape& s) const {
	for (int i = 0; i < NUM_CUBES; i++) {
		if (s.body[i].getY() == 1)
			return true;
	}
	return false;
}
