#ifndef MAIN_H
#define MAIN_H

#include <SDL.h>

bool Initialize();
void Run();
void Tick();
void Close();
void Render();
void HandleInput(SDL_Event e);

#endif