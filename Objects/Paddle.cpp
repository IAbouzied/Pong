#include "Paddle.h"
#include "Graphics.h"
#include "Ball.h"

Paddle::Paddle()
{

}

Paddle::Paddle(Graphics &graphics)
{
	paddleTexture = graphics.loadTexture("Sprites/Paddle.png");
	y = 470 - 96;
	maxJumpVel = -15;
	maxFallVel = 15;
	jumpBoost = -15;
}

void Paddle::move(Ball &ball)
{
	y = y + velocity;
	velocity = velocity + 1;

	//Collision detection
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

	//Velocity constraints
	if (velocity > maxFallVel)
	{
		velocity = maxFallVel;
	}
	if (velocity < maxJumpVel)
	{
		velocity = maxJumpVel;
	}

	//Let the ball detect if it should bounce
	ball.bounceOffPaddle(velocity, y, false);
}

void Paddle::render(Graphics &graphics)
{
	SDL_Rect renderQuad = { 10, y, 32, 96 };
	graphics.blitSurface(paddleTexture, NULL, &renderQuad);
}

//Takes input to jump.
void Paddle::handleEvent(SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE)
	{
		velocity = jumpBoost;
	}
}

