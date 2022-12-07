#include "GameClass.h"
#include "GameClassEnding.h"



Ending::Ending()
{
	// For Texture
	
	SDL_Surface* temp_surface = IMG_Load("../../Resources/ending.jpg");
	texture_ = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	SDL_FreeSurface(temp_surface);

	SDL_QueryTexture(texture_, NULL, NULL, &source_rectangle_.w, &source_rectangle_.h);
	destination_rectangle_.x = 0;
	destination_rectangle_.y = 0;
	source_rectangle_.x = 0;
	source_rectangle_.y = 0;
	destination_rectangle_.w = source_rectangle_.w - 100;
	destination_rectangle_.h = source_rectangle_.h - 100;

	//RetryButton
	r_button_rect.x = 190;
	r_button_rect.y = 425;
	r_button_rect.w = 220;
	r_button_rect.h = 85;
}

Ending::~Ending()
{
	SDL_DestroyTexture(texture_);
}

void Ending::Update()
{
}


void Ending::Render()
{
	SDL_SetRenderDrawColor(g_renderer, 255,255,0,255);
	SDL_RenderClear(g_renderer); // clear the renderer to the draw color

	SDL_RenderCopy(g_renderer, texture_, &source_rectangle_, &destination_rectangle_);

	//Retry
	/*{
		SDL_SetRenderDrawColor(g_renderer, 255, 0, 0, 0);
		SDL_RenderFillRect(g_renderer, &r_button_rect);
	}*/

	SDL_RenderPresent(g_renderer); // draw to the screen
}



void Ending::HandleEvents()
{
	SDL_Event event;
	if(SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			g_flag_running = false;
			break;

		case SDL_MOUSEBUTTONDOWN:
		
			// If the mouse left button is pressed. 
			if ( event.button.button == SDL_BUTTON_LEFT )
			{
				int mouse_x = event.button.x;
				int mouse_y = event.button.y;

				if (mouse_x > r_button_rect.x && mouse_y > r_button_rect.y
					&& mouse_x < r_button_rect.x + r_button_rect.w
					&& mouse_y < r_button_rect.y + r_button_rect.h) {
					g_current_game_phase = PHASE_INTRO;
				}
			}
			break;

		default:
			break;
		}
	}
}
