#include "Scoreboard.h"
#include "Graphics.h"

Scoreboard::Scoreboard() {}

Scoreboard::Scoreboard(Graphics &graphics)
{
	scoreTexture = graphics.loadTexture("Sprites/Scoreboard.png");
}

//Renders the scores.
void Scoreboard::render(Graphics &graphics, int playerScore, int cpuScore)
{
	//Each number is 128px on the sprite sheet
	int pyCord = 128 * playerScore;
	int eyCord = 128 * cpuScore;

	SDL_Rect RpaddleScore = { 0, pyCord, 128, 128 };
	SDL_Rect paddleRQ = { 0, 0, 128, 128 };
	SDL_Rect RenemyScore = { 0, eyCord, 128, 128 };
	SDL_Rect EnemyRQ = { 320, 0, 128, 128 };

	graphics.blitSurface(scoreTexture, &RpaddleScore, &paddleRQ);
	graphics.blitSurface(scoreTexture, &RenemyScore, &EnemyRQ);
}
