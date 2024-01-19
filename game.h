#pragma once
#include "board.h"
#include"general.h"

class Game
{
	Board board1 { GameConfig::MIN_X1 };
	Board board2 { GameConfig::MIN_X2 };
public:
	void run();
	//Game();  // ctor - set keys
};

