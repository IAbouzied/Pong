#include <SDL_image.h>
#include <iostream>

#include "Graphics.h"
#include "Globals.h"


Graphics::Graphics() {

}

Graphics::~Graphics() {

}

void Graphics::blitSurface(SDL_Texture* texture, SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle) {
	SDL_RenderCopy(_renderer, texture, sourceRectangle, destinationRectangle);
}

//Function for giving textures their image.
SDL_Texture* Graphics::loadTexture(std::string path) {
	//Loads a texture through this process. Texture made. Surface made. Texture made into surface. Surface deleted. Texture returned.
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	newTexture = SDL_CreateTextureFromSurface(_renderer, loadedSurface);
	SDL_FreeSurface(loadedSurface);

	return newTexture;
}

//Loads all of the pictures needed.
void Graphics::setBackground(std::string path) {
	//Backgroung picture.
	_background = loadTexture(path);
}

void Graphics::flip() {
	SDL_RenderPresent(_renderer);
}

void Graphics::clear() {
	SDL_RenderClear(_renderer);
	SDL_RenderCopy(_renderer, _background, NULL, NULL);
}

//Initializes the window, renderer, and PNG/SDL_Image stuff
bool Graphics::init() {
	bool success = true;

	//Initialize SDL. < 0 means that initialization failed.
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "Couldnt initialize SDL" << std::endl;
		success = false;
	}
	else
	{
		//Creating the window.
		_window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT, NULL);
		if (_window == NULL)
		{
			std::cout << "Couldnt create window" << std::endl;
			success = false;
		}
		else
		{
			//Creating the renderer. The Flags make the renderer match the monitor refresh rate.
			_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (_renderer == NULL)
			{
				std::cout << "Couldnt create renderer" << std::endl;
				success = false;
			}
			else
			{
				//Setting the renderer color. Still not sure why this has to be done.
				SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Making it possible to load PNG images.
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					std::cout << "Couldnt initialize SDL_Image" << std::endl;
					success = false;
				}
				setBackground("Sprites/LoadingScreen.png");
			}
		}
	}

	return success;
}

//Shuts down everything before exiting the application.
void Graphics::close() {
	//Exits out of everything. Ball and Paddle sprites not included.
	SDL_DestroyWindow(_window);
	SDL_DestroyTexture(_background);
	_background = NULL;
	SDL_DestroyRenderer(_renderer);
	_window = NULL;
	_renderer = NULL;
	IMG_Quit();
	SDL_Quit();
}

SDL_Renderer* Graphics::getRenderer() const {
	return _renderer;
}