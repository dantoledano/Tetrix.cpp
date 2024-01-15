#include "board.h"

Board::Board() //ctor
{
    for (int i = 0; i < GameConfig::GAME_HEIGHT; ++i) {
        for (int j = 0; j < GameConfig::GAME_WIDTH; ++j) {
            matrix[i][j] = ' ';
        }
    }
}




