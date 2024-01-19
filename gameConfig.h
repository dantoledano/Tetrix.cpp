#pragma once
class GameConfig
{
public:
	enum class eKeys { LEFT = 'a', LEFT_CAP = 'A', RIGHT = 'd', RIGHT_CAP = 'D', DROP = 'x', DROP_CAP= 'X',
		               ROTATE = 's', ROTATE_CAP = 'S', CROTATE = 'w', CROTATE_CAP = 'W', DOWN = 'z', ESC = 27 };

	//enum class eKeysPlayer2 {
	//	LEFT = 'j', LEFT_CAP = 'J', RIGHT = 'l', RIGHT_CAP = 'L', DROP = 'm', DROP_CAP = 'M',
	//	ROTATE = 'k', ROTATE_CAP = 'K', CROTATE = 'i', CROTATE_CAP = 'I', DOWN = 'z', ESC = 27};

	static constexpr int GAME_WIDTH = 12;
	static constexpr int GAME_HEIGHT = 18;

	static constexpr int MIN_X1 = 15;
	static constexpr int MIN_X2 = 45;
	static constexpr int MIN_Y = 3;


};
