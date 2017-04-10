#ifndef MAINMENU_H
#define MAINMENU_H

#include <SDL_ttf.h>
#include <SDL.h>
#include <string>
#include <vector>
#include "Button.h"
#include "GamepadInput.h"
#include "Screen.h"

class MainMenu : public Screen {
	public:
		MainMenu(SDL_Renderer *renderer);
		~MainMenu();
		void Tick(GamepadInput *gamepadInput);
		void Render();
		void ChangeSelectedOption(GamepadInput *gamepadInput);
		SDL_Texture* LoadTextTexture(std::string text, SDL_Color textColor, SDL_Renderer *renderer);
		void SelectOption(GamepadInput *gamepadInput);
	private:
		SDL_Renderer *renderer;
		TTF_Font *font;
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
};

#endif