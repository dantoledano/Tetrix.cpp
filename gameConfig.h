#pragma once
class GameConfig
{
public:
	enum class eKeys {LEFT = 'a', RIGHT = 'd', DOWN = 'z', ESC = 27};

	static constexpr int GAME_WIDTH = 12;
	static constexpr int GAME_HEIGHT = 18;

	static constexpr int MIN_X1 = 15;
	static constexpr int MIN_X2 = 45;
	static constexpr int MIN_Y = 3;


};
