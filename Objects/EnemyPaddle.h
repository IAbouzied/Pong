#ifndef ENEMYPADDLE_H
#define ENEMYPADDLE_H

class Graphics;
class Ball;
struct SDL_Texture;

class EnemyPaddle
{
public:
	EnemyPaddle();

	EnemyPaddle(Graphics &graphics);

	void move(Ball &ball);

	void jump();

	void render(Graphics &graphics);

private:
	int y;
	SDL_Texture* paddleTexture;
	int maxJumpVel;
	int maxFallVel;
	int jumpBoost;
	int velocity;
};

#endif