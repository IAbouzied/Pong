#include <SDL.h>
#include <iostream>
#include <SDL_image.h>
#include <string>
#include <cmath>
#include <Windows.h>

#include "Objects/Globals.h"
#include "Objects/Graphics.h"
#include "Objects/Ball.h"
#include "Objects/Scoreboard.h"

//These variables were made so that the classes could interact.
int playerScore = 0;
int cpuScore = 0;

class Paddle
{
public:
	//Initializes the paddle with all of its characteristics.
	Paddle()
	{

	}

	Paddle(Graphics &graphics)
	{
		paddleTexture = graphics.loadTexture("Sprites/Paddle.png");
		y = 470 - 96;
		maxJumpVel = -15;
		maxFallVel = 15;
		jumpBoost = -15;
	}

	//Moves the paddle based on the velocity. Then changes the velocity. Also puts limits on minimum and maximum values. Updates global variables.
	void move(Ball &ball)
	{
		y = y + velocity;
		velocity = velocity + 1;

		if (y < 10)
		{
			y = 10;
			velocity = 0;
		}
		if (y > 470 - 96)
		{
			y = 470 - 96;
			velocity = 0;
		}
		if (velocity > maxFallVel)
		{
			velocity = maxFallVel;
		}
		if (velocity < maxJumpVel)
		{
			velocity = maxJumpVel;
		}

		ball.bounceOffPaddle(velocity, y, false);
	}

	//Renders the paddle to the screen.
	void render(Graphics &graphics)
	{
		SDL_Rect renderQuad = { 10, y, 32, 96 };
		graphics.blitSurface(paddleTexture, NULL, &renderQuad);
	}

	//Takes input to jump.
	void handleEvent(SDL_Event& e)
	{
		if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE)
		{
			velocity = jumpBoost;
		}
	}
private:
	int y;
	int velocity;
	int maxJumpVel;
	int maxFallVel;
	int jumpBoost;
	SDL_Texture* paddleTexture;
};

//Pretty much the same as 'Paddle'. Just small differences in AI.
class EnemyPaddle
{
public:
	EnemyPaddle() {}

	EnemyPaddle(Graphics &graphics)
	{
		paddleTexture = graphics.loadTexture("Sprites/EnemyPaddle.png");
		y = 470 - 96;
		maxJumpVel = -15;
		maxFallVel = 15;
		jumpBoost = -15;
		velocity = 0;
	}

	void move(Ball &ball)
	{
		y = y + velocity;
		velocity = velocity + 1;

		if (y < 10)
		{
			y = 10;
			velocity = 0;
		}
		if (y > 470 - 96)
		{
			y = 470 - 96;
			velocity = 0;
		}
		if (velocity > maxFallVel)
		{
			velocity = maxFallVel;
		}
		if (velocity < maxJumpVel)
		{
			velocity = maxJumpVel;
		}

		if (ball.isMovingRight() && y - 48 > ball.getBallHeight() && velocity > -13)
		{
			jump();
		}

		ball.bounceOffPaddle(velocity, y, true);
	}

	void jump()
	{
		velocity = jumpBoost;
	}

	void render(Graphics &graphics)
	{
		SDL_Rect renderQuad = { globals::SCREEN_WIDTH - 42, y, 32, 96 };
		graphics.blitSurface(paddleTexture, NULL, &renderQuad);
	}

private:
	int y;
	SDL_Texture* paddleTexture;
	int maxJumpVel;
	int maxFallVel;
	int jumpBoost;
	int velocity;
};

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