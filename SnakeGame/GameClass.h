#pragma once

#include <iostream>
#include <string>
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "SDL_image.h"

void InitGame();
void ClearGame();

// Game Phases
const int PHASE_INTRO = 0;
const int PHASE_STAGE1 = 1;
const int PHASE_ENDING = 2;

extern int g_current_game_phase;
extern bool g_flag_running;
extern SDL_Renderer* g_renderer;
extern SDL_Window* g_window;