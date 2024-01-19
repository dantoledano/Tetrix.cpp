#include "shape.h"
#include "point.h"
#include "gameConfig.h"
#include <windows.h>
#include "general.h"


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

//bool Shape::play(Board& board) {
//	Shape s;
//	bool isGameOver = false;
//	int direction;
//	while (!isGameOver) {
//		s.init(randomType(), board);
//		while (!s.hasReachedBottom(s) && !s.hasReachedToAnotherShape(s, board) && !isGameOver)
//		{
//			Sleep(500);
//			int keyPressed = 'z'; // down
//			if (_kbhit())
//			{
//				keyPressed = _getch();
//				if (keyPressed == 27)// ESC
//					break;
//			}
//			direction= checkKeyPressed(keyPressed, board);
//			s.move(direction, s, board);
//		}
//		isGameOver = s.isGameOver(s);
//	}
//	return isGameOver;
//}

//int Shape::checkKeyPressed(int keyPressed,Shape& Leftshape, Shape& RightShape) {
//	for (int i = 0; i < 5; i++) {
//		if (keyPressed == board.keys[i]) {
//			return i;
//		}
//	}
//	return -1;
//}


bool Shape::isShapeOver(Shape& s,Board& board) {
	return (s.hasReachedBottom(s) || s.hasReachedToAnotherShape(s, board));
}
void Shape::eraseShape(int left, int top)
{
	for (int i = 0; i < 4; i++) {
		body[i].draw(' ', left, top);
	}
}


void Shape::drawShape(int left, int top)
{
	for (int i = 0; i < 4; i++) {
		body[i].draw('#', left, top);
	}
}

void Shape::move(Shape& s, Board& board) { //int direction,
	int activeX, activeY;
		//eraseShape(board.getLeft(), GameConfig::MIN_Y);
		//switch (direction)
		//{
		//case 0: //LEFT
		//	moveShapeToTheLeft(s, GameConfig::eKeys::LEFT, board);
		//	break;
		//case 1:
		//	moveShapeToTheRight(s, GameConfig::eKeys::RIGHT, board);
		//	break;
		//	
		//case 2:
		//	if (s.id == 'O') {
		//		moveShapeDown(s, GameConfig::eKeys::DOWN, board);
		//		break;
		//	}
		//	rotateClockwise(s, board);
		//	break;
		//case 3:
		//	if (s.id == 'O') {
		//		moveShapeDown(s, GameConfig::eKeys::DOWN, board);
		//		break;
		//	}
		//	rotateCounterClockwise(s, board);
		//	break;
		//case 4:
		//	dropShape(s, board);
		//	break;
		//case 27:
		//	break;
		//default:
		//	moveShapeDown(s, GameConfig::eKeys::DOWN , board);
		//	break;
		//}
		drawShape(board.getLeft(), GameConfig::MIN_Y);  // re-drawing of the shape at new location
		if (hasReachedBottom(s) || hasReachedToAnotherShape(s, board))  // update matrix
		{
			eraseShape(board.getLeft(), GameConfig::MIN_Y);
			for (int i = 0; i < 4; i++)
			{
				activeX = s.body[i].getX();
				activeY = s.body[i].getY();
				board.matrix[activeY - 1][activeX - 1] = '#';
			}
			board.DrawBoard();
			board.clearFullLines();
		}
}
//void Shape::move(GameConfig::eKeys direction, Shape& s, Board& board)
//{
//	int activeX, activeY;
//	eraseShape(board.getLeft(), GameConfig::MIN_Y);
//	switch (direction)
//	{
//	case GameConfig::eKeys::ROTATE:
//	case GameConfig::eKeys::ROTATE_CAP:
//		if (s.id == 'O') {
//			moveShapeDown(s, GameConfig::eKeys::DOWN, board);
//			break;
//		}
//		rotateClockwise(s, board);
//		break;
//	case GameConfig::eKeys::CROTATE:
//	case GameConfig::eKeys::CROTATE_CAP:
//		if (s.id == 'O') {
//			moveShapeDown(s, GameConfig::eKeys::DOWN, board);
//			break;
//		}
//		rotateCounterClockwise(s, board);
//		break;
//	case GameConfig::eKeys::DROP:
//	case GameConfig::eKeys::DROP_CAP:
//		dropShape(s, board);
//		break;
//	case GameConfig::eKeys::ESC:
//		break;
//	case GameConfig::eKeys::RIGHT:
//	case GameConfig::eKeys::RIGHT_CAP:
//		moveShapeToTheRight(s, direction, board);
//		break;
//	case GameConfig::eKeys::LEFT:
//	case GameConfig::eKeys::LEFT_CAP:
//		moveShapeToTheLeft(s, direction, board);
//		break;
//	default:
//		moveShapeDown(s, direction, board);
//		break;
//	}
//	drawShape(board.getLeft(), GameConfig::MIN_Y);  // re-drawing of the shape at new location
//	if (hasReachedBottom(s) || hasReachedToAnotherShape(s, board))  // update matrix
//	{
//		eraseShape(board.getLeft(), GameConfig::MIN_Y);
//		for (int i = 0; i < 4; i++)
//		{
//			activeX = s.body[i].getX();
//			activeY = s.body[i].getY();
//			board.matrix[activeY - 1][activeX - 1] = '#';
//		}
//		board.DrawBoard();
//		board.clearFullLines();
//	}
//}



bool Shape::collidedWithAnotherShape(const Shape& s, GameConfig::eKeys direction, Board& board)
{
	for (int i = 0; i < 4; i++)
	{
		if (board.matrix[s.body[i].getY() - 1][s.body[i].getX() - 1] == '#')
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
		temp.body[i].movePoint(GameConfig::eKeys::LEFT);
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
	if (currentShape.id == 'O')
		return;
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
	if (currentShape.id == 'O')
		return;
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
	while (!hasReachedBottom(*this) && !hasReachedToAnotherShape(*this, board)) {
		// Erase the shape from the current position
		eraseShape(board.getLeft(), GameConfig::MIN_Y);

		// Move the shape down
		for (int i = 0; i < 4; i++) {
			body[i].movePoint(GameConfig::eKeys::DOWN);
		}

		// Draw the shape at the new position
		drawShape(board.getLeft(), GameConfig::MIN_Y);

		Sleep(30);
	}
	//// Drop the shape until it reaches the bottom of the game screen
	//while (!hasReachedBottom(s) && !hasReachedToAnotherShape(s, board))
	//{
	//	for (int i = 0; i < 4; i++)
	//	{
	//		body[i].draw(' ', board.getLeft(), GameConfig::MIN_Y);
	//		body[i].movePoint(GameConfig::eKeys::DOWN);
	//	}
	//	for (int i = 0; i < 4; i++)
	//		body[i].draw('#', board.getLeft(), GameConfig::MIN_Y);
	//	Sleep(30);
	//}
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


bool Shape::isGameOver(const Shape& s) const {
	for (int i = 0; i < 4; i++) {
		if (s.body[i].getY() == 1) {
			gotoxy(30, 0);
			//std::cout << "game over";
			return true;
		}
	}
	return false;
}
