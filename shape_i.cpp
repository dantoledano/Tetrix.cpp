#include "shape_i.h"


void SHAPE_I::initI(char ch)
{
	// initializing coordinates of shape I
	body[0].initPoint((GameConfig::GAME_WIDTH / 2) - 1, 1);
	body[1].initPoint((GameConfig::GAME_WIDTH / 2), 1);
	body[2].initPoint((GameConfig::GAME_WIDTH / 2) + 1, 1);
	body[3].initPoint((GameConfig::GAME_WIDTH / 2) + 2, 1);
	// printing shape I
	for (int i = 0; i < 4; i++)
	{
		body[i].draw(ch);
	}	
}



void SHAPE_I::move(GameConfig::eKeys direction)
{
	for (int i = 0; i < 4; i++)
	{
		// earasing the shape and then moving all coordinates in given direction
		body[i].draw(' ');
		body[i].movePoint(direction);

	}
	// re-drawing of the shape
	for (int i = 0; i < 4; i++)
	{
		body[i].draw('#');
	}
}
