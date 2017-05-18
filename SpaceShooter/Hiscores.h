#ifndef HISCORES_H
#define HISCORES_H

#include <SDL_ttf.h>
#include <SDL.h>
#include <string>
#include <vector>
#include "Button.h"
#include "Database.h"
#include "HiscoreEntry.h"
#include "GamepadInput.h"
#include "KeyboardInput.h"
#include "Screen.h"

class Hiscores : public Screen {
	public:
		Hiscores(SDL_Renderer *renderer, Database *database);
		~Hiscores();
		void Tick(Inputs *inputs);
		void PopulateHiscoreEntries();
		void ChangeSelectedOption(Inputs *inputs);
		void SelectOption(Inputs *inputs);
		void Render();
	private:
		SDL_Renderer *renderer;
		Database *database;
		TTF_Font *font;
		std::vector<Button*> buttons;
		SDL_Color white;
		SDL_Color selectedColor;
		int selectedOption;
		SDL_Rect rankTextRect;
		SDL_Rect playerNameTextRect;
		SDL_Rect dateTextRect;
		SDL_Rect scoreTextRect;
		SDL_Texture *rankTextTexture;
		SDL_Texture *playerNameTextTexture;
		SDL_Texture *dateTextTexture;
		SDL_Texture *scoreTextTexture;
		std::vector<std::vector<std::string>> topTenHiscores;
		std::vector<HiscoreEntry*> hiscoreEntries;
		Button *backButton;
		Button *resetHiscoresButton;
		Time currentTickTime;
		Time previousTickTime;
		Nanoseconds optionSwapCooldown;
		Nanoseconds optionSwapCooldownLeft;
		Nanoseconds optionSelectCooldown;
		Nanoseconds optionSelectCooldownLeft;
};

#endif