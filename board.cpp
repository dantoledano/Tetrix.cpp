#include "board.h"
#include "point.h"
#include "general.h"
#include "gameConfig.h"
using namespace std;


Board::Board(int xPos, int score) : xPos(xPos), score(score)
{ // initializing the board to be empty.
    for (int i = 0; i < GameConfig::GAME_HEIGHT; ++i) {
        for (int j = 0; j < GameConfig::GAME_WIDTH; ++j) {
            matrix[i][j] = GameConfig::SPACE;
        }
    }
}


void Board::resetBoard()
{ // empty the board.
    for (int i = 0; i < GameConfig::GAME_HEIGHT; ++i) {
        for (int j = 0; j < GameConfig::GAME_WIDTH; ++j) {
            matrix[i][j] = GameConfig::SPACE;
        }
    }
   // setFooAt(0, 0, '*');
}


void Board::setKeys(char leftKey, char rightKey, char rotateKey, char crotateKey, char dropKey)
{
    this->keys[0] = leftKey;
    this->keys[1] = rightKey;
    this->keys[2] = rotateKey;
    this->keys[3] = crotateKey;
    this->keys[4] = dropKey;
}


void Board::drawBorder() const
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
        matrix[0][col] = GameConfig::SPACE;
    }
}


bool Board::isFullLine(int line) const {
    for (int i = 0; i < GameConfig::GAME_WIDTH; i++) {
        if (matrix[line][i] == GameConfig::SPACE)
            return false;
    }
    return true;
}


int Board::clearFullLines() {
    int combo = 0;
    for (int i = 0; i < GameConfig::GAME_HEIGHT; i++) {
        if (isFullLine(i)) {
            eraseLine(i);
            DrawBoard();
            combo++;
        }
    }
    return combo;
}

void Board::organizeBoard()
{
    for (int i = GameConfig::GAME_HEIGHT-2; i >= 0; i--) {
        for (int j = GameConfig::GAME_WIDTH-1; j >= 0; j--){
            int count = 0;
            while ((matrix[i+count][j] == GameConfig::BLOCK) && (matrix[i+1+count][j] == GameConfig::SPACE)) {
                matrix[i+count][j] = GameConfig::SPACE;
                matrix[i+1+count][j] = GameConfig::BLOCK;
                count++;
                if (i + 1 + count > GameConfig::GAME_HEIGHT-1)
                    break;  // end of board
            }
        }
    }
}



void Board::DrawCubeInBoard(int x, int y, char ch) {
    gotoxy(x + xPos, y + GameConfig::MIN_Y);
    cout << ch;
}


void Board::DrawBoard() {
    for (int i = GameConfig::GAME_HEIGHT - 1; i >= 0; i--) {
        for (int j = 0; j < GameConfig::GAME_WIDTH; j++) {
            if (matrix[i][j] == GameConfig::BLOCK) {
                DrawCubeInBoard(j, i, GameConfig::BLOCK);
            }
            else {
                DrawCubeInBoard(j, i, ' ');
            }
        }
    }
}


void Board::expload(int activeX, int activeY)
{
    int count = 1;
    while (count < 5) { // right
        if (activeX + count > GameConfig::GAME_WIDTH-1)
            break;
        matrix[activeY][activeX + count] = GameConfig::SPACE;
        count++;
    }
    count = 1;
    while (count < 5) { // left
        if (activeX - count < 0)
            break;
        matrix[activeY][activeX - count] = GameConfig::SPACE;
        count++;
    }
    count = 1;
    while (count < 5){ // down
        if (activeY + count > GameConfig::GAME_HEIGHT-1)
            break;
        matrix[activeY + count][activeX] = GameConfig::SPACE;
        count++;
    }
    count = 1;
    while (count < 5) { // up
        if (activeY - count < 0)
            break;
        matrix[activeY - count][activeX] = GameConfig::SPACE;
        count++;
    }
}












