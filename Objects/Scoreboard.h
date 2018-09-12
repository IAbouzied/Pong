#ifndef SCOREBOARD_H
#define SCOREBOARD_H

class Graphics;
struct SDL_Texture;

class Scoreboard
{
public:
	Scoreboard();

	Scoreboard(Graphics &graphics);

	//Renders the scores.
	void render(Graphics &graphics, int playerScore, int cpuScore);
private:
	SDL_Texture* scoreTexture;
};


#endif
