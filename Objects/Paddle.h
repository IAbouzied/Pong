#ifndef PADDLE_H
#define PADDLE_H

class Graphics;
class Ball;
union SDL_Event;
struct SDL_Texture;

class Paddle
{
public:
	//Initializes the paddle with all of its characteristics.
	Paddle();

	Paddle(Graphics &graphics);

	//Moves the paddle based on the velocity. Then changes the velocity. Also puts limits on minimum and maximum values. Updates global variables.
	void move(Ball &ball);

	//Renders the paddle to the screen.
	void render(Graphics &graphics);

	//Takes input to jump.
	void handleEvent(SDL_Event& e);
private:
	int y;
	int velocity;
	int maxJumpVel;
	int maxFallVel;
	int jumpBoost;
	SDL_Texture* paddleTexture;
};


#endif