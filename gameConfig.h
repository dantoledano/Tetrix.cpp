#pragma once
class GameConfig
{
public:
	enum class eKeys { LEFT = 'a', RIGHT = 'd', DROP = 'x', ROTATE = 's', CROTATE = 'w', DOWN = 'z', ESC = 27, UP='g'};

	enum class eKeys2 { LEFT = 'j', RIGHT = 'l', DROP = 'm', ROTATE = 'k', CROTATE = 'i', DOWN = 'z', ESC = 27 };

	static constexpr int NUM_KEYS = 5;

	static constexpr int GAME_WIDTH = 12;
	static constexpr int GAME_HEIGHT = 18;

	static constexpr int MIN_X1 = 15;
	static constexpr int MIN_X2 = 45;
	static constexpr int MIN_Y = 3;

	static constexpr char BOMB = '@';
	static constexpr char BLOCK = '#';
	static constexpr char SPACE = ' ';

};
