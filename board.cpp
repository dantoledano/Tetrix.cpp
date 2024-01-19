#include "board.h"
#include "point.h"
#include "general.h"
#include <Windows.h>
using namespace std;


Board::Board(int xPos): xPos(xPos) //ctor
{
    for (int i = 0; i < GameConfig::GAME_HEIGHT; ++i) {
        for (int j = 0; j < GameConfig::GAME_WIDTH; ++j) {
            matrix[i][j] = ' ';
        }
    }
}


//void Board::setKeys(char leftKey, char rightKey, char rotateKey, char crotateKey, char dropKey)
//{
//    this->keys[0] = leftKey;
//    this->keys[1] = rightKey;
//    this->keys[2] = rotateKey;
//    this->keys[3] = crotateKey;
//    this->keys[4] = dropKey;
//}


void Board::drawBorder()
{
    for (int col = xPos; col < GameConfig::GAME_WIDTH + xPos; col++)
    {
        gotoxy(col, GameConfig::MIN_Y - 1);
        cout << "-";

        gotoxy(col, GameConfig::GAME_HEIGHT + GameConfig::MIN_Y);
        cout << "-";
    }

    for (int row = GameConfig::MIN_Y - 1; row <= GameConfig::GAME_HEIGHT + GameConfig::MIN_Y; row++)
    {
        gotoxy(xPos - 1, row);
        cout << "|";

        gotoxy(GameConfig::GAME_WIDTH + xPos, row);
        cout << "|";
    }
}



void Board::eraseLine(int indexLine) {
    for (int i = indexLine; i > 0; i--) {
        for (int col = 0; col < GameConfig::GAME_WIDTH; col++) {
            matrix[i][col] = matrix[i - 1][col];

        }
    }
    for (int col = 0; col < GameConfig::GAME_WIDTH; col++) {
        matrix[0][col] = ' ';
    }
}


bool Board::isFullLine(int line) const {
    for (int i = 0; i < GameConfig::GAME_WIDTH; i++) {
        if (matrix[line][i] == ' ')
            return false;
    }
    return true;
}


void Board::clearFullLines() {
    for (int i = 0; i < GameConfig::GAME_HEIGHT; i++) {
        if (isFullLine(i)) {
            eraseLine(i);
            DrawBoard();
        }
    }
}


void Board::DrawCubeInBoard(int x, int y, char ch) {
    gotoxy(x + xPos, y + GameConfig::MIN_Y); ///
    std::cout << ch;
}


void Board::DrawBoard() {
    for (int i = GameConfig::GAME_HEIGHT - 1; i >= 0; i--) {
        for (int j = 0; j < GameConfig::GAME_WIDTH; j++) {
            if (matrix[i][j] == '#') {
                DrawCubeInBoard(j, i, '#');
            }
            else {
                DrawCubeInBoard(j, i, ' ');
            }
        }
    }
}















