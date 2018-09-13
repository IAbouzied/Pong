#ifndef GAME_H
#define GAME_H

#include "Graphics.h"

class Game {
public:
	Game();
	void loop();
private:
	Graphics _graphics;
	int _playerScore;
	int _cpuScore;
};

#endif