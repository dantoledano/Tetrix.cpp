#include "board.h"

Board::Board() //ctor
{
    for (int i = 0; i < GameConfig::GAME_WIDTH; ++i) {
        for (int j = 0; j < GameConfig::GAME_HEIGHT; ++j) {
            matrix[i][j] = ' ';
        }
    }
}


char* Board::getMatrix() 
{
    return &matrix[0][0];
}


