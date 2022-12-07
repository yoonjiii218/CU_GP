#pragma once

#include "SDL.h"
#include <cstdlib>
#include <ctime>

class Stage1
{
public:
	Stage1();
	~Stage1();

	void InitGame();
	void HandleEvents();
	void Update();
	void Render();

private:
	SDL_Texture* texture_; // the SDL_Texture 
	SDL_Rect source_rectangle_; // the rectangle for source image
	SDL_Rect destination_rectangle_; // for destination
	SDL_Rect snake_destination;
};


