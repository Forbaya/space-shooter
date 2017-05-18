#ifndef MAINMENU_H
#define MAINMENU_H

#include <SDL_ttf.h>
#include <SDL.h>
#include <string>
#include <vector>
#include "Button.h"
#include "GamepadInput.h"
#include "KeyboardInput.h"
#include "Screen.h"

class MainMenu : public Screen {
	public:
		MainMenu(SDL_Renderer *renderer);
		virtual ~MainMenu();
		void Tick(Inputs *inputs);
		void Render();
		void ChangeSelectedOption(Inputs *inputs);
		void SelectOption(Inputs *inputs);
	private:
		SDL_Renderer *renderer;
		std::vector<Button*> buttons;
		SDL_Texture *logoTexture;
		SDL_Rect logoRect;
		SDL_Color white;
		SDL_Color selectedColor;
		int selectedOption;
		Time currentTickTime;
		Time previousTickTime;
		Nanoseconds optionSwapCooldown;
		Nanoseconds optionSwapCooldownLeft;
		Nanoseconds optionSelectCooldown;
		Nanoseconds optionSelectCooldownLeft;
};

#endif