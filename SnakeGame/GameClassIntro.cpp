#include "GameClass.h"
#include "GameClassIntro.h"

Intro::Intro()
{
	// For Texture
	
	SDL_Surface* temp_surface = IMG_Load("../../Resources/intro.jpg");
	texture_ = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	SDL_FreeSurface(temp_surface);

	SDL_QueryTexture(texture_, NULL, NULL, &source_rectangle_.w, &source_rectangle_.h);
	destination_rectangle_.x = source_rectangle_.x = 0;
	destination_rectangle_.y = source_rectangle_.y = 0;
	destination_rectangle_.w = source_rectangle_.w - 100;
	destination_rectangle_.h = source_rectangle_.h - 100;

	//StartButton
	s_button_rect.x = 190;
	s_button_rect.y = 420;
	s_button_rect.w = 200;
	s_button_rect.h = 80;
}

Intro::~Intro()
{
	SDL_DestroyTexture(texture_);
}

void Intro::Update()
{

}


void Intro::Render()
{
	SDL_SetRenderDrawColor(g_renderer, 255,255,255,255);
	SDL_RenderClear(g_renderer); // clear the renderer to the draw color

	SDL_RenderCopy(g_renderer, texture_, &source_rectangle_, &destination_rectangle_);

	SDL_RenderPresent(g_renderer); // draw to the screen
}



void Intro::HandleEvents()
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

				if (mouse_x > s_button_rect.x && mouse_y > s_button_rect.y
					&& mouse_x < s_button_rect.x + s_button_rect.w
					&& mouse_y < s_button_rect.y + s_button_rect.h) {
					g_current_game_phase = PHASE_STAGE1;
				}
			}
			break;

		default:
			break;
		}
	}
}
