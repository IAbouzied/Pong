#include <Windows.h>

#include "Objects/Globals.h"
#include "Objects/Graphics.h"
#include "Objects/Ball.h"
#include "Objects/Scoreboard.h"
#include "Objects/Paddle.h"
#include "Objects/EnemyPaddle.h"

//These variables were made so that the classes could interact.
int playerScore = 0;
int cpuScore = 0;

int main(int argc, char* args[]) 
{
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
			scoreboard.render(graphics, playerScore, cpuScore);

			//Moving
			paddle.move(ball);
			enemyPaddle.move(ball);
			scoreChange = ball.move();

			//Rendering
			paddle.render(graphics);
			ball.render(graphics);
			enemyPaddle.render(graphics);
		}

		if (scoreChange == 1) playerScore++;
		else if (scoreChange == -1) cpuScore++;

		if (playerScore > 10)
		{
			gameOver = true;
			gameStarted = false;
			graphics.setBackground("Sprites/WinScreen.png");
			graphics.clear();
		}

		if (cpuScore > 10)
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
	return 0;
}