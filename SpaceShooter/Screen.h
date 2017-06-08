#ifndef SCREEN_H
#define SCREEN_H

#include <SDL_ttf.h>
#include <SDL.h>
#include "Inputs.h"

class Screen {
	protected:
		bool running;
		int nextScreen;
		TTF_Font *font;
		SDL_Color white;
	public:
		Screen();
		virtual ~Screen();
		virtual void Tick(Inputs *inputs);
		virtual void Render();
		bool IsRunning();
		int GetNextScreen();
		void SetRunning(bool running);
		void SetNextScreen(int nextScreen);
		SDL_Texture *LoadTextTexture(std::string text, SDL_Color textColor, SDL_Renderer *renderer);
};

#endif
