#include "game.h"
using namespace std;

const int EXIT_CHOICE = 9;
const int INSTRUCTIONS_CHOICE = 8;
const int PAUSE_CHOICE = 2;
const int NEW_GAME_CHOICE = 1;

Game::Game() // ctor- setting each playr's keys and the pace of the game
{
	//board1.setKeys('a', 'd', 's', 'w', 'x');
	board1.setKeys((char)GameConfig::eKeys::LEFT, (char)GameConfig::eKeys::RIGHT,
		(char)GameConfig::eKeys::ROTATE, (char)GameConfig::eKeys::CROTATE, (char)GameConfig::eKeys::DROP);
	//board2.setKeys('j', 'l', 'k', 'i', 'm');
	board2.setKeys((char)GameConfig::eKeys2::LEFT, (char)GameConfig::eKeys2::RIGHT,
		(char)GameConfig::eKeys2::ROTATE, (char)GameConfig::eKeys2::CROTATE, (char)GameConfig::eKeys2::DROP);
	pace = 400;
}


void Game::printMenu() { //handling menu and end of the game.
	int choice = 0;
	int winner = -1;
	while (choice != EXIT_CHOICE) {
		printWelcome();
		cin >> choice;
		if (choice == INSTRUCTIONS_CHOICE) {
			printInstructionsAndKeys();
		}
		if (choice == PAUSE_CHOICE && getIsPaused()) {
			system("cls");
			run(choice, winner);
		}
		if (choice == NEW_GAME_CHOICE) {
			system("cls");
			board1.resetBoard();
			board2.resetBoard();
			board1.setScore(0);
			board2.setScore(0);
			run(choice, winner);
		}
	}
	printWinner(winner); // end of the game
}


void Game::run(int& choise, int& winner) {// game loop:
	board1.drawBorder();
	board1.DrawBoard();
	board2.drawBorder();
	board2.DrawBoard();
	Shape s1, s2;
	bool isPlayer1Won = false;
	bool isPlayer2Won = false;
	bool isShapeOver1 = true;
	bool isShapeOver2 = true;
	while (true) {
		printScore(board1, board2);
		deployShape(isShapeOver1, isShapeOver2, s1, s2);
		Sleep(pace);
		char keyPressed = (char)GameConfig::eKeys::DOWN;
		if (_kbhit())
		{
			keyPressed = _getch();
			if (keyPressed == (char)GameConfig::eKeys::ESC) {
				setIsPaused(true); // game is paused - returning to the menu 
				return;
			}
		}
		keyPressed = invertToLowerCase(keyPressed); // in case of uppercase keys
		//clearing the shape befor re-draw at new location
		s1.eraseShape(board1.getLeft(), GameConfig::MIN_Y);
		s2.eraseShape(board2.getLeft(), GameConfig::MIN_Y);

		if (keyPressed == '0') {
			s1.moveShapeDown(board1);
			s2.moveShapeDown(board2);
		}
		// moving according to key- meaning according to the key we move the
		// player that obtains the key and moving down the other player.
		checkKeyPressed(keyPressed, s1, s2);
		isShapeOver1 = s1.isShapeOver(board1);
		isShapeOver2 = s2.isShapeOver(board2);
		if (isShapeOver1 && isShapeOver2)
		{ // handling shapes when there done.
			isPlayer1Won = s2.isGameOver();
			isPlayer2Won = s1.isGameOver();
			if (isPlayer1Won && isPlayer2Won)
				break;
			continue;
		}
		else if (isShapeOver1) {
			isPlayer2Won = s1.isGameOver();
			s1.init(randomType(), board1);
		}
		else if (isShapeOver2) {
			isPlayer1Won = s2.isGameOver();
			s2.init(randomType(), board2);
		}
		if (isPlayer1Won || isPlayer2Won)
			break;
	}
	if (isPlayer1Won && isPlayer2Won) { // tie
		winner = (board1.getScore() > board2.getScore()) ? 1 : ((board2.getScore() > board1.getScore()) ? 2 : 0);
	}
	else {
		winner = (isPlayer1Won) ? 1 : 2; // checking who won
	}
	choise = EXIT_CHOICE; // the player has chose to exit the game
}


void Game::printWinner(int num) const {
	system("cls");
	if (num == 0)
		printItsTie();
	else if (num == 1)
		printWinnerIs1();
	else if (num == 2)
		printWinnerIs2();
	else
		printGameOver();
}


void Game::printScore(Board& board1, Board& board2) const {
	gotoxy(10, 0);
	cout << "Player's 1 score is: " << board1.getScore();
	gotoxy(40, 0);
	cout << "Player's 2 score is: " << board2.getScore();
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


char Game::invertToLowerCase(char ch) {
	// checking if key is valid and converting to lower case.
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
		//case 'z':
	case (char)GameConfig::eKeys::DOWN:
		LeftShape.moveShapeDown(board1);
		RightShape.moveShapeDown(board2);
		break;
		//case 'a':
	case (char)GameConfig::eKeys::LEFT:
		LeftShape.moveShapeToTheLeft(board1);
		RightShape.moveShapeDown(board2);
		break;
		//case 'd':
	case (char)GameConfig::eKeys::RIGHT:
		LeftShape.moveShapeToTheRight(board1);
		RightShape.moveShapeDown(board2);
		break;
		//case 's':
	case (char)GameConfig::eKeys::ROTATE:
		LeftShape.rotateClockwise(board1);
		RightShape.moveShapeDown(board2);
		break;
		//case 'w':
	case (char)GameConfig::eKeys::CROTATE:
		LeftShape.rotateCounterClockwise(board1);
		RightShape.moveShapeDown(board2);
		break;
		//case 'x':
	case (char)GameConfig::eKeys::DROP:
		RightShape.moveShapeDown(board2);
		RightShape.move(board2);
		LeftShape.dropShape(board1);
		break;
		//case 'j':
	case (char)GameConfig::eKeys2::LEFT:
		RightShape.moveShapeToTheLeft(board2);
		LeftShape.moveShapeDown(board1);
		break;
		//case 'l':
	case (char)GameConfig::eKeys2::RIGHT:
		RightShape.moveShapeToTheRight(board2);
		LeftShape.moveShapeDown(board1);
		break;
		//case 'k':
	case (char)GameConfig::eKeys2::ROTATE:
		RightShape.rotateClockwise(board2);
		LeftShape.moveShapeDown(board1);
		break;
		//case 'i':
	case (char)GameConfig::eKeys2::CROTATE:
		RightShape.rotateCounterClockwise(board2);
		LeftShape.moveShapeDown(board1);
		break;
		//case 'm':
	case (char)GameConfig::eKeys2::DROP:
		LeftShape.moveShapeDown(board1);
		LeftShape.move(board1);
		RightShape.dropShape(board2);
		break;
	default:
		break;
	}
	LeftShape.move(board1);
	RightShape.move(board2);

}


void Game::printInstructionsAndKeys() const {
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


void Game::printTableLine() const {
	cout << "---------------------------------------------------------\n";
}


void Game::printWinnerIs1() const
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


void Game::printWinnerIs2() const
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


void Game::printItsTie() const
{
	cout << "    ___ _   _                 _   _      _  " << endl;
	cout << "   |_ _| |_( )___     __ _   | |_(_) ___| | " << endl;
	cout << "    | || __|// __|   / _` |  | __| |/ _ \\ | " << endl;
	cout << "    | || |_  \\__ \\  | (_| |  | |_| |  __/_| " << endl;
	cout << "   |___|\\__| |___/   \\__,_|   \\__|_|\\___(_) " << endl;
}


void Game::printWelcome() const
{
	system("cls");
	cout << "__        __   _                             _                " << endl;
	cout << "\\ \\      / /__| | ___ ___  _ __ ___   ___   | |_ ___        " << endl;
	cout << " \\ \\ /\\ / / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\  | __/   \\ " << endl;
	cout << "  \\ V  V /  __/ | (_| (_) | | | | | |  __/  | || (_) |     " << endl;
	cout << "   \\_/\\_/ \\___|_|\\___\\___/|_| |_| |_|\\___|   \\__\\___/ \n" << endl;
	cout << "               _       _        _     _    " << endl;
	cout << "              | |_ ___| |_ _ __(_)___| | " << endl;
	cout << "              | __/ _ \\ __| '__| / __| |  " << endl;
	cout << "              | ||  __/ |_| |  | \\__ \\_|  " << endl;
	cout << "               \\__\\___|\\__|_|  |_|___(_)   " << endl;
	cout << "\n" << endl;


	cout << "(1) Start a new game" << endl;
	if (getIsPaused())
		cout << "(2) Continue a paused game" << endl;
	cout << "(8) Present instructions and keys" << endl;
	cout << "(9) EXIT" << endl;
}


void Game::printGameOver() const
{
	cout << "   ____                          ___                 " << endl;
	cout << "  / ___| __ _ _ __ ___   ___    / _ \\__   _____ _ __ " << endl;
	cout << " | |  _ / _` | '_ ` _ \\ / _ \\  | | | \\ \\ / / _ \\ '__|" << endl;
	cout << " | |_| | (_| | | | | | |  __/  | |_| |\\ V /  __/ |   " << endl;
	cout << "  \\____|\\__,_|_| |_| |_|\\___|   \\___/  \\_/ \\___|_|   " << endl;
}
