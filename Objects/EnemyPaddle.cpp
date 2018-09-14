#include "Ball.h"
#include "Graphics.h"
#include "EnemyPaddle.h"
#include "Globals.h"


EnemyPaddle::EnemyPaddle() {}

EnemyPaddle::EnemyPaddle(Graphics &graphics)
{
	paddleTexture = graphics.loadTexture("Sprites/EnemyPaddle.png");
	y = 470 - 96;
	maxJumpVel = -15;
	maxFallVel = 15;
	jumpBoost = -15;
	velocity = 0;
}

void EnemyPaddle::move(Ball &ball)
{
	y = y + velocity;
	velocity = velocity + 1;
	
	//Collision detection
	if (y < 10) {
		y = 10;
		velocity = 0;
	}
	if (y > 470 - 96) {
		y = 470 - 96;
		velocity = 0;
	}
	//Velocity constraints
	if (velocity > maxFallVel) {
		velocity = maxFallVel;
	}
	if (velocity < maxJumpVel) {
		velocity = maxJumpVel;
	}

	//Deciding whether AI should jump
	if (ball.isMovingRight() && y - 48 > ball.getBallHeight() && velocity > -13)
	{
		jump();
	}

	ball.bounceOffPaddle(velocity, y, true);
}

void EnemyPaddle::jump()
{
	velocity = jumpBoost;
}

void EnemyPaddle::render(Graphics &graphics)
{
	SDL_Rect renderQuad = { globals::SCREEN_WIDTH - 42, y, 32, 96 };
	graphics.blitSurface(paddleTexture, NULL, &renderQuad);
}
