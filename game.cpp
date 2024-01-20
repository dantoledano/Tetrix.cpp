#include "game.h"
using namespace std;


Game::Game()
{
	board1.setKeys('a', 'd', 's', 'w', 'x');
	board2.setKeys('j', 'l', 'k', 'i', 'm');
}


void Game::printMenu() {
	int choise = 0;
	int winner = -1;
	while (choise != 9) {
		printWelcome();
		cin >> choise;
		if (choise == 8) {
			printInstructionsAndKeys();
		}
		if (choise == 2) {
			system("cls");
			run(choise, winner);		
		}
		if (choise == 1){
			system("cls");
			board1.resetBoard();
			board2.resetBoard();
			run(choise, winner);
		}
	}
	printWinner(winner);
}


void Game::run(int& choise, int& winner) {
	board1.drawBorder();
	board1.DrawBoard();
	board1.setKeys('a', 'd', 's', 'w', 'x');
	board2.drawBorder();
	board2.DrawBoard();
	board2.setKeys('j', 'l', 'k', 'i', 'm');
	Shape s1, s2;
	int direction;
	bool isPlayer1Won = false;
	bool isPlayer2Won = false;
	bool isShapeOver1 = true;
	bool isShapeOver2 = true;

	while (true) {
		deployShape(isShapeOver1, isShapeOver2, s1, s2);
		Sleep(500);
		char keyPressed = 'z'; // down
		if (_kbhit())
		{
			keyPressed = _getch();
			if (keyPressed == (int)GameConfig::eKeys::ESC) {
				setIsPaused(true);
				return;
			}		
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
		winner = 0;
	else if (isPlayer1Won)
		winner = 1;
	else
		winner = 2;
	choise = 9; // the game is over
}


void Game::printWinner(int num) {
	system("cls");
	if (num == 0)
		printItsTie();
	else if (num == 1)
		printWinnerIs1();
	else if (num == 2)
		printWinnerIs2();
	else
		cout << "bye" << endl;  // אני אסדר את זה מחר שזה יהיה נורמלי
}



void Game::deployShape(bool& l, bool& r, Shape& s1, Shape& s2) {
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
	for (int i = 0; i < 5; i++) {
		if (board1.keys[i] == ch || board1.keys[i] == (ch + ('a' - 'A'))
			|| board2.keys[i] == ch || board2.keys[i] == (ch + ('a' - 'A')))
		{
			if (ch >= 'A' && ch <= 'Z')
				return ch + ('a' - 'A');
			if (ch >= 'a' && ch <= 'z')
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


void Game::printInstructionsAndKeys() {
	system("cls");
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
	cout << "DROP                    |    x or X     |    m or M     |\n\n\n";
	cout << "press any key to continue...\n" << endl;
	while (true)
	{
		if (_kbhit())
		{
			_getch(); // clean the buffer
			return;
		}
	}
}


void Game::printTableLine() {
	cout << "---------------------------------------------------------\n";
}


void Game::printWinnerIs1()
{
	cout << " ____  _                           _   " << endl;
	cout << "|  _ \\| | __ _ _   _  ___ _ __    / | " << endl;
	cout << "| |_) | |/ _` | | | |/ _ \\ '__|   | | " << endl;
	cout << "|  __/| | (_| | |_| |  __/ |      | | " << endl;
	cout << "|_|   |_|\\__,_|\\__, |\\___|_|      |_| " << endl;
	cout << "               |___/                    " << endl;
	cout << "\n" << endl;
	cout << " _        _   _                      _                       _ " << endl;
	cout << "(_)___   | |_| |__   ___   __      _(_)_ __  _ __   ___ _ __| |" << endl;
	cout << "| / __|  | __| '_ \\ / _ \\  \\ \\ /\\ / / | '_ \\| '_ \\ / _ \\ '__| |" << endl;
	cout << "| \\__ \\  | |_| | | |  __/   \\ V  V /| | | | | | | |  __/ |  |_|" << endl;
	cout << "|_|___/   \\__|_| |_|\___|     \\_/\\_/ |_|_| |_|_| |_|\\___|_|  (_)" << endl;
}


void Game::printWinnerIs2()
{
	cout << " ____  _                          ____  " << endl;
	cout << "|  _ \\| | __ _ _   _  ___ _ __   |___ \\  " << endl;
	cout << "| |_) | |/ _` | | | |/ _ \\ '__|    __) |" << endl;
	cout << "|  __/| | (_| | |_| |  __/ |      / __/  " << endl;
	cout << "|_|   |_|\\__,_|\\__, |\\___|_|     |_____|" << endl;
	cout << "               |___/                     " << endl;
	cout << "\n" << endl;
	cout << " _        _   _                      _                       _ " << endl;
	cout << "(_)___   | |_| |__   ___   __      _(_)_ __  _ __   ___ _ __| |" << endl;
	cout << "| / __|  | __| '_ \\ / _ \\  \\ \\ /\\ / / | '_ \\| '_ \\ / _ \\ '__| |" << endl;
	cout << "| \\__ \\  | |_| | | |  __/   \\ V  V /| | | | | | | |  __/ |  |_|" << endl;
	cout << "|_|___/   \\__|_| |_|\___|     \\_/\\_/ |_|_| |_|_| |_|\\___|_|  (_)" << endl;
}


void Game::printItsTie()
{
	cout << "    ___ _   _                 _   _      _  " << endl;
	cout << "   |_ _| |_( )___     __ _   | |_(_) ___| | " << endl;
	cout << "    | || __|// __|   / _` |  | __| |/ _ \\ | " << endl;
	cout << "    | || |_  \\__ \\  | (_| |  | |_| |  __/_| " << endl;
	cout << "   |___|\\__| |___/   \\__,_|   \\__|_|\\___(_) " << endl;
}


void Game::printWelcome()
{
	system("cls");
	cout << "__        __   _                             _           _____    _        _        " << endl;
	cout << "\\ \\      / /__| | ___ ___  _ __ ___   ___   | |_ ___    |_   _|__| |_ _ __(_)___  " << endl;
	cout << " \\ \\ /\\ / / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\  | __/ _ \\     | |/ _ \\ __| '__| / __| " << endl;
	cout << "  \\ V  V /  __/ | (_| (_) | | | | | |  __/  | || (_) |    | |  __/ |_| |  | \\__ \\ " << endl;
	cout << "   \\_/\\_/ \\___|_|\\___\\___/|_| |_| |_|\\___|   \\__\\___/     |_|\\___|\\__|_|  |_|___/" << endl;
	cout << "\n" << endl;
	cout << "(1) Start a new game" << endl;
	if(getIsPaused())
		cout << "(2) Continue a paused game" << endl;
	cout << "(8) Present instructions and keys" << endl;
	cout << "(9) EXIT"<< endl;
}
