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
	//All the processes needed to begin.
	Graphics graphics;
	graphics.init();
	SDL_Event e;
	Paddle paddle(graphics);
	Ball ball(graphics);
	EnemyPaddle enemyPaddle(graphics);
	Scoreboard scoreboard(graphics);

	//Some variables for flow control.
	bool gameStarted = false;
	bool quit = false;
	bool gameOver = false;

	//Main game loop.
	while (!quit)
	{
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
						graphics.setBackground("Sprites/GameBackground.png");
						gameStarted = true;
					}
				}
			}
			paddle.handleEvent(e);
		}

		graphics.clear();
		int scoreChange = 0;

		//Game loop
		if (gameStarted == true)
		{
			scoreboard.render(graphics, _playerScore, _cpuScore);

			//Moving
			paddle.move(ball);
			enemyPaddle.move(ball);
			scoreChange = ball.move();

			//Rendering
			paddle.render(graphics);
			ball.render(graphics);
			enemyPaddle.render(graphics);
		}

		if (scoreChange == 1) _playerScore++;
		else if (scoreChange == -1) _cpuScore++;

		if (_playerScore > 10)
		{
			gameOver = true;
			gameStarted = false;
			graphics.setBackground("Sprites/WinScreen.png");
			graphics.clear();
		}

		if (_cpuScore > 10)
		{
			gameOver = true;
			gameStarted = false;
			graphics.setBackground("Sprites/LoseScreen.png");
			graphics.clear();
		}

		graphics.flip();
		if (scoreChange != 0) Sleep(globals::SLEEP_TIME);
	}

	graphics.close();
}
