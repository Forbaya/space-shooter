#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <SDL_ttf.h>
#include <SDL.h>
#include <string>
#include "Button.h"
#include "Screen.h"

class Instructions : public Screen {
	public:
		Instructions(SDL_Renderer *renderer);
		virtual ~Instructions();
		void Tick(Inputs *inputs);
		void SelectOption(Inputs *inputs);
		void Render();
	private:
		SDL_Renderer *renderer;
		Button *backButton;
		Time currentTickTime;
		Time previousTickTime;
		Nanoseconds optionSelectCooldown;
		Nanoseconds optionSelectCooldownLeft;
		SDL_Rect firstRowRect;
		SDL_Rect secondRowRect;
		SDL_Rect thirdRowRect;
		SDL_Rect fourthRowRect;
		SDL_Rect fifthRowRect;
		SDL_Rect sixthRowRect;
		SDL_Rect seventhRowRect;
		SDL_Rect eighthRowRect;
		SDL_Rect ninthRowRect;
		SDL_Rect tenthRowRect;
		SDL_Rect eleventhRowRect;
		SDL_Texture *firstRowTexture;
		SDL_Texture *secondRowTexture;
		SDL_Texture *thirdRowTexture;
		SDL_Texture *fourthRowTexture;
		SDL_Texture *fifthRowTexture;
		SDL_Texture *sixthRowTexture;
		SDL_Texture *seventhRowTexture;
		SDL_Texture *eighthRowTexture;
		SDL_Texture *ninthRowTexture;
		SDL_Texture *tenthRowTexture;
		SDL_Texture *eleventhRowTexture;
};

#endif