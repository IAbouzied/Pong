#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <map>
#include <string>
#include <SDL.h>

class Graphics {
public:
	Graphics();
	~Graphics();

	void blitSurface(SDL_Texture* texture, SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle);
	//Function for giving textures their image.
	SDL_Texture* loadTexture(std::string path);
	//Loads all of the pictures needed.
	void setBackground(std::string path);

	void flip();
	void clear();

	//Initializes the window, renderer, and PNG/SDL_Image stuff
	bool init();
	//Shuts down everything before exiting the application.
	void close();

	SDL_Renderer* getRenderer() const;
private:
	SDL_Window* _window;
	SDL_Renderer* _renderer;
	SDL_Texture* _background;
};

#endif