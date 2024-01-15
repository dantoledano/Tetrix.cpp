#pragma once
#include "gameConfig.h"
#include "board.h"

class Board
{
// private:
public: 
	char matrix[GameConfig::GAME_HEIGHT][GameConfig::GAME_WIDTH];
    Board(); //ctor
};

