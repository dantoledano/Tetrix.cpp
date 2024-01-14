#pragma once
#include "gameConfig.h"
#include "board.h"

class Board
{
private:
	char matrix[GameConfig::GAME_WIDTH][GameConfig::GAME_HEIGHT];
public:
    Board(); //ctor
	char* getMatrix();

};

