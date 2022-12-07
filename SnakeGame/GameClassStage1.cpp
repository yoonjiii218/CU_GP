#include "GameClass.h"
#include "GameClassStage1.h"
#include <vector>
#include <list>

//SnakeNode
class Snake 
{
public:
	Snake() 
	{
		x = 0;
		y = 0;
	}

	Snake(float _x, float _y)
	{
		x = _x;
		y = _y;
	}

	float x;
	float y;
};

int g_elapsed_time;
int g_last_time;

int snake_state = 50;
bool isGameover;
bool isNew;
std::list<Snake> S;

SDL_Rect iteam_destination;
bool isDisapear=true;
bool isSame;
int ran_x;
int ran_y;

SDL_Rect go_destination;

//font
SDL_Texture* g_gameOver;
SDL_Rect g_gameOver_rect;
SDL_Texture* g_clickAnywhere;
SDL_Rect g_clickAnywhere_rect;

Stage1::Stage1()
{
	g_elapsed_time = 0;

	//snake
	snake_destination.x = 300;
	snake_destination.y = 300;
	snake_destination.w = 30;
	snake_destination.h = 30;

	//iteam
	iteam_destination.x = 150;
	iteam_destination.y = 210;
	iteam_destination.w = 30;
	iteam_destination.h = 30;

	//gameOver
	go_destination.x = 0;
	go_destination.y = 0;
	go_destination.w = 600;
	go_destination.h = 600;

	//font
	TTF_Font* font1 = TTF_OpenFont("../../Resources/BMDOHYEON_ttf.ttf", 100);
	SDL_Color black = { 0, 0, 0, 0 };

	//gameover
	{
		SDL_Surface* tmp_surface = TTF_RenderText_Blended(font1, "Game Over", black);
		g_gameOver_rect.x = 0;
		g_gameOver_rect.y = 0;
		g_gameOver_rect.w = tmp_surface->w;
		g_gameOver_rect.h = tmp_surface->h;

		g_gameOver = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);
		SDL_FreeSurface(tmp_surface);
	}

	//clickanywhere
	{
		SDL_Surface* tmp_surface = TTF_RenderText_Blended(font1, "Click anywhere", black);
		g_clickAnywhere_rect.x = 0;
		g_clickAnywhere_rect.y = 0;
		g_clickAnywhere_rect.w = tmp_surface->w;
		g_clickAnywhere_rect.h = tmp_surface->h;

		g_clickAnywhere = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);
		SDL_FreeSurface(tmp_surface);
	}


	TTF_CloseFont(font1);

	S.push_back(Snake(300, 300)); //Head
}

Stage1::~Stage1()
{
	SDL_DestroyTexture(texture_);
}

void Stage1::InitGame() {
	g_elapsed_time = 0;
	g_last_time = 0;
	snake_state = 50;
	isGameover = false;
	isNew = false;
	S.clear();

	//snake
	snake_destination.x = 300;
	snake_destination.y = 300;
	snake_destination.w = 30;
	snake_destination.h = 30;

	//iteam
	iteam_destination.x = 150;
	iteam_destination.y = 210;
	iteam_destination.w = 30;
	iteam_destination.h = 30;

	S.push_back(Snake(300, 300));

	isDisapear = true;
	isSame = false;
}

void Stage1::Update()
{

	if (isNew && !isGameover) {
		isNew = false;
		S.push_back(Snake(S.end()->x, S.end()->y));
	}

	Snake prev = Snake(S.begin()->x, S.begin()->y);
	Snake current;
	int i = 0;

	if (g_elapsed_time - g_last_time > 70) {
		if (!isGameover) {
			g_last_time = g_elapsed_time;

			if (snake_state == 1) {
				S.begin()->x += 30;
			}
			else if (snake_state == 2) {
				S.begin()->x -= 30;
			}
			else if (snake_state == 3) {
				S.begin()->y += 30;
			}
			else if (snake_state == 4) {
				S.begin()->y -= 30;
			}
		}


		for (auto iter = S.begin(); iter != S.end(); iter++) {
			i++;
			if (iter != S.begin() && snake_state < 5) {
				current.x = iter->x;
				current.y = iter->y;
				iter->x = prev.x;
				iter->y = prev.y;
				prev.x = current.x;
				prev.y = current.y;
			}
		}
	}

	int k = 0;
	for (auto iter = S.begin(); iter != S.end(); iter++) {
		k++;
		if (k > 3) {
			if (S.begin()->x == iter->x) {
				if (S.begin()->y + 30 == iter->y || S.begin()->y - 30 == iter->y) {
					isGameover = true;
				}
			}
			else if (S.begin()->y == iter->y) {
				if (S.begin()->x + 30 == iter->x || S.begin()->x - 30 == iter->x) {
					isGameover = true;
				}
			}
		}

		if (isGameover)
			break;
	}

	if ((S.begin()->x <= 0 || S.begin()->x >= 570
		|| S.begin()->y <= 0 || S.begin()->y >= 570) && !isGameover) {
		snake_state = 130;
		isGameover = true; 
	}

	if (S.begin()->x == iteam_destination.x && S.begin()->y == iteam_destination.y) {
		isDisapear = true;
		isNew = true;
	}

	if (isDisapear) {
		isDisapear = false;
		srand(time(NULL));
		ran_x = (rand() % 18 + 1) * 30;
		ran_y = (rand() % 18 + 1) * 30;

		iteam_destination.x = ran_x;
		iteam_destination.y = ran_y;
	}

	g_elapsed_time += 33;
}


void Stage1::Render()
{
	SDL_SetRenderDrawColor(g_renderer, 255,255,255,0);
	SDL_RenderClear(g_renderer); // clear the renderer to the draw color

	//DrawLine
	SDL_SetRenderDrawColor(g_renderer, 189, 189, 189, 255);
	for (int i = 1; i < 20; i++) {
		SDL_RenderDrawLine(g_renderer, 30 * i, 0, 30 * i, 600);
	}
	for (int k = 1; k < 20; k++) {
		SDL_RenderDrawLine(g_renderer, 0, 30 * k, 600, 30 * k);
	}

	if (!isDisapear) {
		//greeniteam
		SDL_SetRenderDrawColor(g_renderer, 0, 255, 0, 255);
		SDL_RenderFillRect(g_renderer, &iteam_destination);
	}
	
	//snakeRect
	SDL_SetRenderDrawColor(g_renderer, 0, 0, 255, 0);
	
	for (auto iter = S.begin(); iter != S.end(); iter++) {
		snake_destination.x = iter->x;
		snake_destination.y = iter->y;
		if(snake_destination.y != 0 && snake_destination.x != 0)
			SDL_RenderFillRect(g_renderer, &snake_destination);
	}

	if (isGameover) {
		SDL_SetRenderDrawColor(g_renderer, 255, 233, 140, 200);
		SDL_RenderFillRect(g_renderer, &go_destination);

		//game over
		{
			SDL_Rect tmp_r;
			tmp_r.x = 110;
			tmp_r.y = 150;
			tmp_r.w = g_gameOver_rect.w / 1.5;
			tmp_r.h = g_gameOver_rect.h / 1.5;
			SDL_RenderCopy(g_renderer, g_gameOver, &g_gameOver_rect, &tmp_r);
		}

		//click anywhere
		{
			SDL_Rect tmp_r;
			tmp_r.x = 150;
			tmp_r.y = 250;
			tmp_r.w = g_clickAnywhere_rect.w / 3;
			tmp_r.h = g_clickAnywhere_rect.h / 3;
			SDL_RenderCopy(g_renderer, g_clickAnywhere, &g_clickAnywhere_rect, &tmp_r);
		}
	}
	
	SDL_RenderPresent(g_renderer); // draw to the screen
}



void Stage1::HandleEvents()
{
	SDL_Event event;
	if(SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			g_flag_running = false;
			break;


		case SDL_KEYDOWN:		
			if (!isGameover) {
				if (event.key.keysym.sym == SDLK_RIGHT) {
					snake_state = 1;
				}
				else if (event.key.keysym.sym == SDLK_LEFT) {
					snake_state = 2;
				}
				else if (event.key.keysym.sym == SDLK_DOWN) {
					snake_state = 3;
				}
				else if (event.key.keysym.sym == SDLK_UP) {
					snake_state = 4;
				}
			}	

			break;

		case SDL_MOUSEBUTTONDOWN:
			if(isGameover)
				g_current_game_phase = PHASE_ENDING;

			break;
		default:
			break;
		}
	}
}
