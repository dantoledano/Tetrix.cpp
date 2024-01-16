#include "board.h"
#include "point.h"
#include "general.h"
#include <Windows.h>


Board::Board() //ctor
{
    for (int i = 0; i < GameConfig::GAME_HEIGHT; ++i) {
        for (int j = 0; j < GameConfig::GAME_WIDTH; ++j) {
            matrix[i][j].setActive(false);
            /*matrix[i][j].setX(j);
            matrix[i][j].setY(i);*/
            //matrix[i][j].draw(' ');
        }
    }
}

void Board::eraseLine(int indexLine) {
    for (int i = indexLine; i > 0; i--) {
        for (int col = 0; col < GameConfig::GAME_WIDTH; col++) {
            matrix[i][col].setActive(matrix[i - 1][col].getActive());
            
        }
    }
    for (int col = 0; col < GameConfig::GAME_WIDTH; col++) {
        matrix[0][col].setActive(false);
    }
}

bool Board::isFullLine(int line) {
    for (int i = 0; i < GameConfig::GAME_WIDTH; i++) {
        if (!matrix[line][i].getActive()) {
            return false;
        }
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
    gotoxy(x + GameConfig::MIN_X, y + GameConfig::MIN_Y);
    std::cout << ch;
}

void Board::DrawBoard(){
    for (int i = GameConfig::GAME_HEIGHT-1; i>=0; i--) {
        for (int j = 0; j < GameConfig::GAME_WIDTH; j++) {
            if (matrix[i][j].getActive()) {
                //matrix[i][j].draw('#');
                DrawCubeInBoard(j, i, '#');
            }
            else {
                //matrix[i][j].draw(' ');
                DrawCubeInBoard(j, i, ' ');
            }
        }
    }
}

bool Board::isGameOver() const {
    for (int i = 0; i < GameConfig::GAME_WIDTH; i++) {
        if (matrix[1][i].getActive()) {
            // If any cell in the top row contains a shape, the game is over
            std::cout << "game over";
            return true;
        }
    }
    return false;
}













