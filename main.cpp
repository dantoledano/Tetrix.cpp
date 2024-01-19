#include "general.h"
using namespace std;



int main()
{
	Game game;
	game.printMenu();
	//game.run();
	gotoxy(0, GameConfig::GAME_HEIGHT + GameConfig::MIN_Y + 2);
}
