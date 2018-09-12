#ifndef BALL_H
#define BALL_H

#include <SDL.h>

class Graphics;

class Ball
{
public:
	Ball();
	Ball(Graphics &graphics);

	//Moves ball and a lot of collision detection. Also some stuff about curving the ball when its hit at an angle.
	int move();

	//Renders the ball to the screen.
	void render(Graphics &graphics);
	bool isMovingRight();
	int getBallHeight();
	void bounceOffPaddle(int paddleVelocity, int yPaddlePos, bool isEnemy);
private:
	int xPos, yPos, xVel, yVel;
	SDL_Texture* ballTexture;
};

#endif