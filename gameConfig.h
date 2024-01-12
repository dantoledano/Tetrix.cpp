#pragma once
class GameConfig
{
public:
	enum class eKeys { LEFT = 'a', RIGHT = 'd', DROP = 'x',ROTATE='s', CROTATE = 'w', DOWN='z', ESC = 27 };

	static constexpr int GAME_WIDTH = 12;
	static constexpr int GAME_HEIGHT = 18;

	static constexpr int MIN_X = 10;
	static constexpr int MIN_Y = 3;

};

