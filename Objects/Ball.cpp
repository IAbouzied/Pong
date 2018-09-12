#include <cmath>
#include <Windows.h>

#include "Ball.h"
#include "Globals.h"
#include "Graphics.h"

Ball::Ball() {}

Ball::Ball(Graphics &graphics)
{
	ballTexture = graphics.loadTexture("Sprites/Ball.png");
	xPos = 480;
	yPos = 224;
	xVel = 10;
	yVel = 5;
}

//Moves ball and a lot of collision detection. Also some stuff about curving the ball when its hit at an angle.
int Ball::move()
{
	int scoreModifier = 0;
	xPos = xPos + xVel;
	yPos = yPos + yVel;


	//Went out right side
	if (xPos > globals::SCREEN_WIDTH)
	{
		xPos = 160;
		yPos = 224;
		yVel = rand() % 19 - 10;
		scoreModifier = 1;
	}
	//Went out left side
	if (xPos < 0)
	{
		xPos = 480;
		yPos = 224;
		yVel = rand() % 19 - 10;
		scoreModifier = -1;
	}
	//Bouncing off top or bottom
	if (yPos > globals::SCREEN_HEIGHT - 32 || yPos < 0)
	{
		yPos -= yVel;
		yVel = -yVel;
	}
	//Capping y-velocity
	if (abs(yVel) > 12)
	{
		yVel = yVel / abs(yVel) * 12;
	}

	return scoreModifier;
}

//Renders the ball to the screen.
void Ball::render(Graphics &graphics)
{
	SDL_Rect renderQuad = { xPos, yPos, 32, 32 };
	graphics.blitSurface(ballTexture, NULL, &renderQuad);
}

bool Ball::isMovingRight() {
	return xVel > 0;
}

int Ball::getBallHeight() {
	return yPos;
}

void Ball::bounceOffPaddle(int paddleVelocity, int yPaddlePos, bool isEnemy) {
	//Being hit by paddles
	if (!isEnemy && xPos / 42 == 1 && xPos % 42 <= std::abs(xVel) && yPos > yPaddlePos - 32 && yPos < yPaddlePos + 96 && xVel < 0)
	{
		xVel = -xVel;
		yVel = yVel + paddleVelocity / 2;
	}
	else if (isEnemy && xPos / (globals::SCREEN_WIDTH - 74) == 1 && xPos % (globals::SCREEN_WIDTH - 74) <= xVel && yPos > yPaddlePos - 32 && yPos < yPaddlePos + 96 && xVel > 0)
	{
		yVel = yVel + paddleVelocity / 2;
		xVel = -xVel;
	}
}

