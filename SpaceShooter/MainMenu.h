#ifndef MAINMENU_H
#define MAINMENU_H

#include <SDL_ttf.h>
#include <SDL.h>
#include <string>
#include "GamepadInput.h"
#include "Screen.h"

class MainMenu : public Screen {
	public:
		MainMenu(SDL_Renderer *renderer);
		~MainMenu();
		void Tick(GamepadInput *gamepadInput);
		void Render();
		SDL_Texture* LoadTextTexture(std::string textureText, SDL_Color textColor);
		void ChangeSelectedOption(GamepadInput *gamepadInput);
	private:
		SDL_Renderer *renderer;
		TTF_Font *font;
		SDL_Texture *logoTexture;
		SDL_Texture *newGameTexture;
		SDL_Texture *hiscoresTexture;
		SDL_Texture *instructionsTexture;
		SDL_Texture *quitTexture;
		SDL_Rect logoRect;
		SDL_Rect newGameRect;
		SDL_Rect hiscoresRect;
		SDL_Rect instructionsRect;
		SDL_Rect quitRect;
		SDL_Color white;
		SDL_Color selected;
		int textTextureWidth;
		int textTextureHeight;
		int selectedOption;
};

#endif