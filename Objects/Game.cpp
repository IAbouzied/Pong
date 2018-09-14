#include <Windows.h>

#include "Game.h"
#include "Globals.h"
#include "Ball.h"
#include "Scoreboard.h"
#include "Paddle.h"
#include "EnemyPaddle.h"

Game::Game() {
	_graphics = Graphics();
	_graphics.init();
	_playerScore = 0;
	_cpuScore = 0;
	loop();
}

void Game::loop() {
	SDL_Event e;
	Paddle paddle(_graphics);
	Ball ball(_graphics);
	EnemyPaddle enemyPaddle(_graphics);
	Scoreboard scoreboard(_graphics);

	bool gameStarted = false;
	bool quit = false;
	bool gameOver = false;

	//Main game loop.
	while (!quit)
	{
		//Event handling
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				SDL_Quit();
				quit = true;
			}
			if (e.type == SDL_KEYDOWN)
			{
				if (e.key.keysym.sym == SDLK_SPACE)
				{
					if (gameStarted == false && gameOver == false)
					{
						_graphics.setBackground("Sprites/GameBackground.png");
						gameStarted = true;
					}
				}
			}
			paddle.handleEvent(e);
		}

		_graphics.clear();

		//Tracks whether anyone has scored
		int scoreChange = 0;

		if (gameStarted == true)
		{
			scoreboard.render(_graphics, _playerScore, _cpuScore);

			//Moving
			paddle.move(ball);
			enemyPaddle.move(ball);
			scoreChange = ball.move();

			//Rendering
			paddle.render(_graphics);
			ball.render(_graphics);
			enemyPaddle.render(_graphics);
		}

		if (scoreChange == 1) _playerScore++;
		else if (scoreChange == -1) _cpuScore++;

		//Game end screens
		if (_playerScore > 10)
		{
			gameOver = true;
			gameStarted = false;
			_graphics.setBackground("Sprites/WinScreen.png");
			_graphics.clear();
		}

		if (_cpuScore > 10)
		{
			gameOver = true;
			gameStarted = false;
			_graphics.setBackground("Sprites/LoseScreen.png");
			_graphics.clear();
		}

		_graphics.flip();
		//Pause time to reset the ball
		if (scoreChange != 0) Sleep(globals::SLEEP_TIME);
	}

	_graphics.close();
}
