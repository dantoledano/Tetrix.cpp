#include "game.h"
using namespace std;


Game::Game() // ctor- setting each playr's keys and the pace of the game
{
	////board1.setKeys('a', 'd', 's', 'w', 'x');
	//board1.setKeys((char)GameConfig::eKeys::LEFT, (char)GameConfig::eKeys::RIGHT,
	//	(char)GameConfig::eKeys::ROTATE, (char)GameConfig::eKeys::CROTATE, (char)GameConfig::eKeys::DROP);
	////board2.setKeys('j', 'l', 'k', 'i', 'm');
	//board2.setKeys((char)GameConfig::eKeys2::LEFT, (char)GameConfig::eKeys2::RIGHT,
	//	(char)GameConfig::eKeys2::ROTATE, (char)GameConfig::eKeys2::CROTATE, (char)GameConfig::eKeys2::DROP);
	pace = PACE;
}


void Game::printMenu() { //handling menu and end of the game.
	int choice = 0;
	int winner = -1;
	while (choice != EXIT_CHOICE) {
		printWelcome(winner);
		cin >> choice;
		if (choice == INSTRUCTIONS_CHOICE) {
			printInstructionsAndKeys();
		}
		if (choice == PAUSE_CHOICE && getIsPaused()) {
			system("cls");
			run(winner); 
		}
		if (choice == NEW_GAME_CHOICE) { 
			system("cls");
			board1.resetBoard();
			board2.resetBoard();
			board1.setScore(0);
			board2.setScore(0);
			run(winner);
		}
		if (winner != -1) {
			printWinner(winner);
			winner = -1; // reset winner for potentially next game
			setIsPaused(false); // reset game status to: not paused
		}
	}
	printGameOver(); // end of game- printing game over and ending the program
}


void Game::run(int& winner) {// game loop:
	displayBoardsAndBorders();
	Shape s1, s2;
	int numRotationPlayer1, numRotationPlayer2;
	int xPositionPlayer1, xPositionPlayer2;
	bool isPlayer1Won = false, isPlayer2Won = false;
	bool isShapeOver1 = true, isShapeOver2 = true;
	bool player1sTurn = true;
	while (true) {
		printScore(board1, board2);
		if (isShapeOver1) { // deploying a new shape and find best move to perform
			s1.init(randomType(), board1);
			board1.findBestMove(s1, numRotationPlayer1, xPositionPlayer1);
			isShapeOver1 = false;
		}
		if (isShapeOver2) {
			s2.init(randomType(), board2);
			board2.findBestMove(s2, numRotationPlayer2, xPositionPlayer2);
			isShapeOver2 = false;
		}
		Sleep(pace);
		char keyPressed = (char)GameConfig::eKeys::DOWN;
		if (_kbhit())
		{
			keyPressed = _getch(); // receive key from user
			if (keyPressed == (char)GameConfig::eKeys::ESC) {
				setIsPaused(true); // game is paused - returning to the menu 
				return;
			}
		}
		if (player1sTurn) { // player 1's turn
			receiveKeyOfPlayer1(s1, keyPressed, numRotationPlayer1, xPositionPlayer1);
			player1sTurn = false;
		}
		else { // player 2's turn
			receiveKeyOfPlayer2(s2, keyPressed, numRotationPlayer2, xPositionPlayer2);
			player1sTurn = true;
		}
		performKeyPressed(keyPressed, s1, s2); // moving player according to key
		preformUpdatesAfterLanding(s1, s2, isShapeOver1, isShapeOver2);
		if (isShapeOver1 && isShapeOver2) // handling shapes when there done.
		{ 
			isPlayer1Won = s2.isGameOver();
			isPlayer2Won = s1.isGameOver();
			if (isPlayer1Won && isPlayer2Won)
				break;
			continue;
		}
		else if (isShapeOver1) {
			isPlayer2Won = s1.isGameOver();
		}
		else if (isShapeOver2) {
			isPlayer1Won = s2.isGameOver();
		}
		if (isPlayer1Won || isPlayer2Won) // ending game loop when someone wins
			break;
	}
	if (isPlayer1Won && isPlayer2Won) { // tie - winning according to score, possibly same score
		winner = (board1.getScore() > board2.getScore()) ? 1 : ((board2.getScore() > board1.getScore()) ? 2 : 0);
	}
	else {
		winner = (isPlayer1Won) ? 1 : 2; // set winner
	}
}


void Game::displayBoardsAndBorders() {
	board1.drawBorder();
	board1.DrawBoard();
	board2.drawBorder();
	board2.DrawBoard();
}


void Game::receiveKeyOfPlayer1(const Shape& s1, char& keyPressed, int& numRotationPlayer1, int& xPositionPlayer1) {
	if (numRotationPlayer1 > 0)
	{
		keyPressed = (char)GameConfig::eKeys::ROTATE;
		numRotationPlayer1--;
	}
	else {
		if (xPositionPlayer1 > s1.getFirstX()) {
			keyPressed = (char)GameConfig::eKeys::RIGHT;
		}
		else if (xPositionPlayer1 < s1.getFirstX()) {
			keyPressed = (char)GameConfig::eKeys::LEFT;
		}
		else {
			keyPressed = (char)GameConfig::eKeys::DROP;
		}
	}
}


void Game::receiveKeyOfPlayer2(const Shape& s2, char& keyPressed, int& numRotationPlayer2, int& xPositionPlayer2) {
	if (numRotationPlayer2 > 0)
	{
		keyPressed = (char)GameConfig::eKeys2::ROTATE;
		numRotationPlayer2--;
	}
	else {
		if (xPositionPlayer2 > s2.getFirstX()) {
			keyPressed = (char)GameConfig::eKeys2::RIGHT;
		}
		else if (xPositionPlayer2 < s2.getFirstX()) {
			keyPressed = (char)GameConfig::eKeys2::LEFT;
		}
		else {
			keyPressed = (char)GameConfig::eKeys2::DROP;
		}
	}
}


void Game::preformUpdatesAfterLanding(Shape& s1, Shape& s2, bool& isShapeOver1, bool& isShapeOver2) {
	if (s1.getHasExploded()) {
		isShapeOver1 = true;
		s1.setHasExploded(false);
	}
	else
		isShapeOver1 = s1.isShapeOver(board1);
	if (s2.getHasExploded()) {
		isShapeOver2 = true;
		s2.setHasExploded(false);
	}
	else
		isShapeOver2 = s2.isShapeOver(board2);
}


void Game::printWinner(int num) const {
	system("cls");
	if (num == 0) {
		printItsTie();
		return;
	}
	else if (num == 1) {
		printWinnerIs1();
		return;
	}
	else {
		printWinnerIs2();
		return;
	}
}


void Game::printScore(Board& board1, Board& board2) const {
	gotoxy(10, 0);
	cout << "Player's 1 score is: " << board1.getScore();
	gotoxy(40, 0);
	cout << "Player's 2 score is: " << board2.getScore();
}


char Game::invertToLowerCase(char ch) {
	// checking if key is valid and converting to lower case.
	for (int i = 0; i < 5; i++) {
		char key1 = board1.getKeysAt(i);
		char key2 = board2.getKeysAt(i);
		if (key1 == ch || key1 == (ch + ('a' - 'A'))
			|| key2 == ch || key2 == (ch + ('a' - 'A')))
		{
			if (ch >= 'A' && ch <= 'Z')
				return ch + ('a' - 'A');
			if (ch >= 'a' && ch <= 'z')
				return ch;
		}
	}
	return '0';
}


void Game::performKeyPressed(char keyPressed, Shape& LeftShape, Shape& RightShape) {
	LeftShape.eraseShape(board1.getLeft(), GameConfig::MIN_Y);
	RightShape.eraseShape(board2.getLeft(), GameConfig::MIN_Y);
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
	getKeyToContinue(); return;
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
	cout << "\n" << endl;
	getKeyToContinue(); return;
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
	cout << "\n" << endl;
	getKeyToContinue(); return;
}


void Game::printItsTie() const
{
	cout << "    ___ _   _                 _   _      _  " << endl;
	cout << "   |_ _| |_( )___     __ _   | |_(_) ___| | " << endl;
	cout << "    | || __|// __|   / _` |  | __| |/ _ \\ | " << endl;
	cout << "    | || |_  \\__ \\  | (_| |  | |_| |  __/_| " << endl;
	cout << "   |___|\\__| |___/   \\__,_|   \\__|_|\\___(_) " << endl;
	cout << "\n" << endl;
	getKeyToContinue(); return;
}


void Game::printWelcome(int& winner) const
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
	if (getIsPaused() && winner == -1)
		cout << "(2) Continue a paused game" << endl;
	cout << "(8) Present instructions and keys" << endl;
	cout << "(9) EXIT" << endl;
}


void Game::printGameOver() const
{
	system("cls");
	cout << "   ____                          ___                 " << endl;
	cout << "  / ___| __ _ _ __ ___   ___    / _ \\__   _____ _ __ " << endl;
	cout << " | |  _ / _` | '_ ` _ \\ / _ \\  | | | \\ \\ / / _ \\ '__|" << endl;
	cout << " | |_| | (_| | | | | | |  __/  | |_| |\\ V /  __/ |   " << endl;
	cout << "  \\____|\\__,_|_| |_| |_|\\___|   \\___/  \\_/ \\___|_|   " << endl;
}
