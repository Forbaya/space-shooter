#ifndef HISCORES_H
#define HISCORES_H

#include <SDL_ttf.h>
#include <SDL.h>
#include <string>
#include <vector>
#include "Button.h"
#include "GamepadInput.h"
#include "KeyboardInput.h"
#include "Screen.h"

class Hiscores : public Screen {
	public:
		Hiscores(SDL_Renderer *renderer);
		~Hiscores();
	private:
		SDL_Renderer *renderer;
		TTF_Font *font;
		std::vector<Button*> buttons;
		SDL_Color white;
		SDL_Color selectedColor;
		int selectedOption;
};

#endif