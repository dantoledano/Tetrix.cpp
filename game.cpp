#include "game.h"
using namespace std;


Game::Game()
{
	board1.setKeys('a', 'd', 's', 'w', 'x');
	board2.setKeys('j', 'l', 'k', 'i', 'm');
}

void Game::run() {
	board1.drawBorder();
	board1.setKeys('a', 'd', 's', 'w', 'x');
	board2.drawBorder();
	board2.setKeys('j', 'l', 'k', 'i', 'm');
	Shape s1, s2;
	int direction;
	bool isPlayer1Won = false;
	bool isPlayer2Won = false;
	bool isShapeOver1 = true;
	bool isShapeOver2 = true;
	//while (!isPlayer1Won && !isPlayer2Won) 
	//{
		while (true) {
			deployShape(isShapeOver1, isShapeOver2, s1, s2);
			Sleep(300);
			char keyPressed = 'z'; // down
			if (_kbhit())
			{
				keyPressed = _getch();
				if (keyPressed == (int)GameConfig::eKeys::ESC)
					break;
			}
			keyPressed = invertToLowerCase(keyPressed);
			s1.eraseShape(board1.getLeft(), GameConfig::MIN_Y);
			s2.eraseShape(board2.getLeft(), GameConfig::MIN_Y);
			if (keyPressed == '0') {
				s1.moveShapeDown(s1, GameConfig::eKeys::DOWN, board1);
				s2.moveShapeDown(s2, GameConfig::eKeys::DOWN, board2);
			}
			checkKeyPressed(keyPressed, s1, s2);
			isShapeOver1 = s1.isShapeOver(s1, board1);
			isShapeOver2 = s2.isShapeOver(s2, board2);
			if (isShapeOver1 && isShapeOver2) {
				isPlayer1Won = s2.isGameOver(s2);
				isPlayer2Won = s1.isGameOver(s1);
				if (isPlayer1Won && isPlayer2Won) {
					break;
				}
				continue;
			}
			else if (isShapeOver1) {
				isPlayer2Won = s1.isGameOver(s1);
				s1.init(randomType(), board1);
			}
			else if (isShapeOver2) {
				isPlayer1Won = s2.isGameOver(s2);
				s2.init(randomType(), board2);
			}
			if (isPlayer1Won || isPlayer2Won) 
				break;
		}

		if (isPlayer1Won && isPlayer2Won)
			printWinner(0);
		else if (isPlayer1Won)
			printWinner(1);
		else
			printWinner(2);
	//}
}

void Game::printWinner(int num) {
	if (num == 0)
		cout << "It's a tie!";
	else
	   cout << "Player #" <<num <<" is the winner!!!";
}

void Game::deployShape(bool& l, bool& r ,Shape& s1, Shape& s2) {
	if (l) {
		s1.init(randomType(), board1);
		l = false;
	}
	if (r) {
		s2.init(randomType(), board2);
		r = false;
	}
}
char Game::invertToLowerCase(char ch) {//בודקת שהתו שנקלט חוקי בכלל ואז אם הוא אות גדולה הופכת אותו לקטנה
	for(int i=0; i<5; i++){
		if (board1.keys[i] == ch || board1.keys[i] == (ch + ('a' - 'A'))
			|| board2.keys[i] == ch || board2.keys[i] == (ch + ('a' - 'A')))
		{
			if (ch >= 'A' && ch <= 'Z')
				return ch + ('a' - 'A');
			if(ch >= 'a' && ch <= 'z')
				return ch;
		}
	}
    return '0';
}

void Game::checkKeyPressed(char keyPressed, Shape& LeftShape, Shape& RightShape) {
	switch (keyPressed) {
	case 'z':
		LeftShape.moveShapeDown(LeftShape, GameConfig::eKeys::DOWN, board1);
		RightShape.moveShapeDown(RightShape, GameConfig::eKeys::DOWN, board2);
		break;
	case 'a':
		LeftShape.moveShapeToTheLeft(LeftShape, GameConfig::eKeys::LEFT, board1);
		RightShape.moveShapeDown(RightShape, GameConfig::eKeys::DOWN, board2);
		break;
	case 'd':
		LeftShape.moveShapeToTheRight(LeftShape, GameConfig::eKeys::RIGHT, board1);
		RightShape.moveShapeDown(RightShape, GameConfig::eKeys::DOWN, board2);
		break;
	case 's':
		LeftShape.rotateClockwise(LeftShape, board1);
		RightShape.moveShapeDown(RightShape, GameConfig::eKeys::DOWN, board2);
		break;
	case 'w':
		LeftShape.rotateCounterClockwise(LeftShape, board1);
		RightShape.moveShapeDown(RightShape, GameConfig::eKeys::DOWN, board2);
		break;
	case 'x':
		RightShape.moveShapeDown(RightShape, GameConfig::eKeys::DOWN, board2);
		RightShape.move(RightShape, board2);
		LeftShape.dropShape(LeftShape, board1);
		break;
	case 'j':
		RightShape.moveShapeToTheLeft(RightShape, GameConfig::eKeys::LEFT, board2);
		LeftShape.moveShapeDown(LeftShape, GameConfig::eKeys::DOWN, board1);
		break;
	case 'l':
		RightShape.moveShapeToTheRight(RightShape, GameConfig::eKeys::RIGHT, board2);
		LeftShape.moveShapeDown(LeftShape, GameConfig::eKeys::DOWN, board1);
		break;
	case 'k':
		RightShape.rotateClockwise(RightShape, board2);
		LeftShape.moveShapeDown(LeftShape, GameConfig::eKeys::DOWN, board1);
		break;
	case 'i':
		RightShape.rotateCounterClockwise(RightShape, board2);
		LeftShape.moveShapeDown(LeftShape, GameConfig::eKeys::DOWN, board1);
		break;
	case 'm':
		LeftShape.moveShapeDown(LeftShape, GameConfig::eKeys::DOWN, board1);
		LeftShape.move(LeftShape, board1);
		RightShape.dropShape(RightShape, board2);
		break;
	default:
		break;
	}
	LeftShape.move(LeftShape, board1);
	RightShape.move(RightShape, board2);
	
}

//void Game::run()
//{
//	board1.drawBorder();
//	board2.drawBorder();
//	Shape s1;
//	Shape s2;
//	bool isGameOver = false;
//	while (!isGameOver)
//	{
//		s1.init(randomType(), board1);
//		s2.init(randomType(), board2);
//		while (!s1.hasReachedBottom(s1) && !s1.hasReachedToAnotherShape(s1, board1))
//		{
//			Sleep(500);
//			int keyPressed = 'z'; // down
//			if (_kbhit())
//			{
//				keyPressed = _getch();
//				if (keyPressed == (int)GameConfig::eKeys::ESC)
//					break;
//			}
//			s1.move((GameConfig::eKeys)keyPressed, s1, board1);
//			s2.move((GameConfig::eKeys)keyPressed, s2, board2);
//		}
//		isGameOver = s1.isGameOver(s1);
//	}
//}

void Game::printMenu() {
	int choise;
	cout << "Welcome to a Tetris Game" << endl;
	cout << "(1) Start a new game" << endl
		<< "(8) Present instructions and keys" << endl
		<< "(9) EXIT" << endl;
	cin >> choise;
	if (choise == 1) {
		system("cls");
		run();
	}
	if (choise == 8) {
		printInstructionsAndKeys();
	}
}

void Game::printInstructionsAndKeys() {
	cout << "In Tetris, you must arrange a sequence of small shapes into complete lines." << endl
		<< "As each line is completed, it will disappear from the screen." << endl
		<< "Tetraminos fall from the top of the play field to the bottom.\n\n";
	cout << "*** Keybinds ***\n\n";
	cout << "                        |  Left Player  |  Right Player |\n";
	printTableLine();
	cout << "LEFT                    |    a or A     |    j or J     |\n";
	printTableLine();
	cout << "RIGHT                   |    d or D     |    l or L     |\n";
	printTableLine();
	cout << "ROTATE clockwise        |    s or S     |    k or K     |\n";
	printTableLine();
	cout << "ROTATE counterClockwise |    w or W     |    i or I     | \n";
	printTableLine();
	cout << "DROP                    |    x or X     |    m or M     |\n";
}

void Game::printTableLine() {
	cout << "---------------------------------------------------------\n";
}

