#include "shape.h"
#include "point.h"
#include "gameConfig.h"
#include <windows.h>
#include "general.h"


void Shape::init(char id, Board& board)
{// init position of shape at the top of the board
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
	default: // '@' BOMB
		for (int i = 0; i < NUM_CUBES; i++)
			body[i].initPoint((GameConfig::GAME_WIDTH / 2), 1);
	}
	drawShape(board.getLeft(), GameConfig::MIN_Y);
}


bool Shape::isShapeOver(Board& board) const {
	// if the shape reached the bottom or landed on another shape
	// it means this current shape has finished it's job.
	return (hasReachedBottom() || hasReachedToAnotherShape(board));
}


void Shape::eraseShape(int left, int top)
{
	for (int i = 0; i < NUM_CUBES; i++) {
		body[i].draw(GameConfig::SPACE, left, top);
	}
}


void Shape::drawShape(int left, int top)
{
	if (id == GameConfig::BOMB)
		body[0].draw(GameConfig::BOMB, left, top);

	else {
		for (int i = 0; i < NUM_CUBES; i++) {
			body[i].draw(GameConfig::BLOCK, left, top);
		}
	}
}


void Shape::move(Board& board) {
	int activeX, activeY;
	int completedLine = 0;
	// re-drawing of the shape at new location
	drawShape(board.getLeft(), GameConfig::MIN_Y);
	if (hasReachedBottom() || hasReachedToAnotherShape(board))
	{
		eraseShape(board.getLeft(), GameConfig::MIN_Y);
		if (id == GameConfig::BOMB) {
			bool shouldOrganize = board.explod(body[0].getX() - 1, body[0].getY() - 1);
			if (shouldOrganize)
				board.organizeBoard();
			setHasExploded(true);
		}
		else {
			updateMatrix(board, true);
		}
		board.DrawBoard();
		completedLine = board.clearFullLines();
		board.setScore(board.getScore() + (completedLine * 100));
		if (completedLine > 1)
			board.setScore(board.getScore() + (completedLine * 50)); //for combos
	}
}



bool Shape::collidedWithAnotherShape(Board& board) const
{   // if the shape is supposed to move to a location where there already
	// is another shape (even a part of it) we rule out the move.
	for (int i = 0; i < NUM_CUBES; i++)
	{
		if (board.getMatrixAt(body[i].getY() - 1, body[i].getX() - 1) == GameConfig::BLOCK)
		{
			return true;
		}
	}
	return false;
}


bool Shape::hasReachedToAnotherShape(Board& board) const
{   // if at a certain point, the shape reaches to another shape
	// meaning it's just above the one under it we stop the shape 
	// from progressing any further.
	for (int i = 0; i < NUM_CUBES; i++)
	{
		if (board.getMatrixAt(body[i].getY(), body[i].getX() - 1) == GameConfig::BLOCK)
			return true;
	}
	return false;
}


void Shape::moveShapeDown(Board& board)
{// taking the shape one step down as long as it didnt reached the
 // bottom and didnt reach another shape - meaning the move is valid.
	if (!hasReachedBottom() && !hasReachedToAnotherShape(board))
	{
		for (int i = 0; i < NUM_CUBES; i++)
		{
			body[i].movePoint(GameConfig::eKeys::DOWN);
		}
	}
}


void Shape::moveShapeToTheLeft(Board& board)
{// taking the shape one step to the left as long as it didnt reached the
 // wall, didnt reach another shape and didnt collid with another shape-
 // meaning the move is valid. for in valid moves we *try* to move the shape down.
	Shape temp = *this;
	for (int i = 0; i < NUM_CUBES; i++)
	{
		temp.body[i].movePoint(GameConfig::eKeys::LEFT);
	}
	if (!hasReachedLeftWall() && !hasReachedToAnotherShape(board) && !temp.collidedWithAnotherShape(board))
	{
		*this = temp;
	}
	else {
		moveShapeDown(board);
	}
}



void Shape::moveShapeToTheRight(Board& board)
{// taking the shape one step to the right as long as it didnt reached the
 // wall, didnt reach another shape and didnt collid with another shape-
 // meaning the move is valid. for in valid moves we *try* to move the shape down.
	Shape temp = *this;
	for (int i = 0; i < NUM_CUBES; i++)
	{
		temp.body[i].movePoint(GameConfig::eKeys::RIGHT);
	}
	if (!hasReachedRightWall() && !hasReachedToAnotherShape(board) && !temp.collidedWithAnotherShape(board))
	{
		*this = temp;
	}
	else {
		moveShapeDown(board);
	}
}



void Shape::rotateCounterClockwise(Board& board)
{// rotating the shape counter clock wise:
 // if the shape is above another shape or if the rotation will cause 
 // a collision - we dont allow the rotation.
 // if the rotation is causing the shape to leave the frames of the board
 // we push the shape back in to the board next to the wall.
	if (this->id == 'O' || id == GameConfig::BOMB) {
		moveShapeDown(board);
		return;
	}
	Shape tempShape = *this;
	// Assuming the first cube is the center of the shape
	int pivotX = tempShape.body[1].getX();
	int pivotY = tempShape.body[1].getY();

	for (int i = 0; i < NUM_CUBES; ++i)
	{// Perform 90-degree counterclockwise rotation
		int relativeX = tempShape.body[i].getX() - pivotX;
		int relativeY = tempShape.body[i].getY() - pivotY;
		tempShape.body[i].setX(pivotX + relativeY);
		tempShape.body[i].setY(pivotY - relativeX);
	}
	tempShape.correctLocationOfShape();  // in case of deviation
	if (!tempShape.hasReachedToAnotherShape(board) && !tempShape.collidedWithAnotherShape(board))
		*this = tempShape; // applaying the rotation only if the move is valid
}


void Shape::rotateClockwise(Board& board)
{// rotating the shape clock wise:
 // if the shape is above another shape or if the rotation will cause 
 // a collision - we dont allow the rotation.
 // if the rotation is causing the shape to leave the frames of the board
 // we push the shape back in to the board next to the wall.
	if (this->id == 'O' || id == GameConfig::BOMB) {
		moveShapeDown(board);
		return;
	}
	Shape tempShape = *this;
	// Assuming the first cube is the center of the shape
	int pivotX = tempShape.body[1].getX();
	int pivotY = tempShape.body[1].getY();

	for (int i = 0; i < NUM_CUBES; ++i)
	{// Perform 90-degree counterclockwise rotation
		int relativeX = tempShape.body[i].getX() - pivotX;
		int relativeY = tempShape.body[i].getY() - pivotY;
		tempShape.body[i].setX(pivotX - relativeY);
		tempShape.body[i].setY(pivotY + relativeX);
	}
	tempShape.correctLocationOfShape(); // in case of deviation
	if (!tempShape.hasReachedToAnotherShape(board) && !tempShape.collidedWithAnotherShape(board))
		*this = tempShape; // applaying the rotation only if the move is valid	
}


void Shape::correctLocationOfShape()
{// after rotation, if needed the function pushes the shape back 
 // in to the board next to the wall.
	while (passedRightWall())
	{
		for (int i = 0; i < NUM_CUBES; i++)
		{
			body[i].movePoint(GameConfig::eKeys::LEFT);
		}
	}
	while (passedLeftWall())
	{
		for (int i = 0; i < NUM_CUBES; i++)
		{
			body[i].movePoint(GameConfig::eKeys::RIGHT);
		}
	}
	while (passedUpperWall())
	{
		for (int i = 0; i < NUM_CUBES; i++)
		{
			body[i].movePoint(GameConfig::eKeys::DOWN);
		}
	}
	while (passedLowerWall())
	{
		for (int i = 0; i < NUM_CUBES; i++)
		{
			body[i].movePoint(GameConfig::eKeys::UP);
		}
	}
}


bool Shape::passedLowerWall() const
{
	for (int i = 0; i < NUM_CUBES; i++)
	{
		if (body[i].getY() > GameConfig::GAME_HEIGHT)
			return true;
	}
	return false;
}


bool Shape::passedUpperWall() const
{
	for (int i = 0; i < NUM_CUBES; i++)
	{
		if (body[i].getY() < 1)
			return true;
	}
	return false;
}


bool Shape::passedRightWall() const
{
	for (int i = 0; i < NUM_CUBES; i++)
	{
		if (body[i].getX() > GameConfig::GAME_WIDTH)
			return true;
	}
	return false;
}


bool Shape::passedLeftWall() const
{
	for (int i = 0; i < NUM_CUBES; i++)
	{
		if (body[i].getX() < 1)
			return true;
	}
	return false;
}


void Shape::dropShape(Board& board)
{
	while (!hasReachedBottom() && !hasReachedToAnotherShape(board)) {
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


bool Shape::hasReachedBottom() const
{
	// Check if any part of the shape has reached the bottom of the game screen
	for (int i = 0; i < NUM_CUBES; i++)
	{
		if (body[i].getY() == GameConfig::GAME_HEIGHT)
			return true;
	}
	return false;
}


bool Shape::hasReachedRightWall() const
{
	for (int i = 0; i < NUM_CUBES; i++)
	{
		if (body[i].getX() >= GameConfig::GAME_WIDTH)
			return true;
	}
	return false;
}


bool Shape::hasReachedLeftWall() const
{
	for (int i = 0; i < NUM_CUBES; i++)
	{
		if (body[i].getX() <= 1)
			return true;
	}
	return false;
}


bool Shape::isGameOver() const {
	for (int i = 0; i < NUM_CUBES; i++) {
		if (body[i].getY() == 1)
			return true;
	}
	return false;
}



int  Shape::getSumOfHeights() const {
	int sum = 0;
	for (int i = 0; i < NUM_CUBES; i++) {
		sum += body[i].getY();
	}
	return sum;
}



int Shape::getHeightOfCube(int i) const {
	return  body[i].getY() - 1;
}


void Shape::updateMatrix(Board& b, bool add) {
	int activeX, activeY;
	for (int i = 0; i < NUM_CUBES; i++) {
		activeX = body[i].getX() - 1;
		activeY = body[i].getY() - 1;
		if (add)
			b.setMatrixAt(activeY, activeX, GameConfig::BLOCK);
		else
			b.setMatrixAt(activeY, activeX, GameConfig::SPACE);
	}
}


int Shape::getFirstX() const {
	int minX = body[0].getX();
	for (int i = 1; i < 4; i++){
		int currX = body[i].getX();
		if (currX < minX)
			minX = currX;
	}
	return minX - 1;
}
