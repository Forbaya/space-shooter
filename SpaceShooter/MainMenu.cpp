#include "MainMenu.h"

MainMenu::MainMenu(SDL_Renderer *renderer) {
	this->renderer = renderer;
	font = TTF_OpenFont("res/roboto.ttf", 24);

	white = { 255, 255, 255 };
	selected = { 255, 255, 0 };
	logoTexture = LoadTextTexture("SPACE SHOOTER!", white);
	newGameTexture = LoadTextTexture("New game", selected);
	hiscoresTexture = LoadTextTexture("Hiscores", white);
	instructionsTexture = LoadTextTexture("Instructions", white);
	quitTexture = LoadTextTexture("Quit", white);

	logoRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, 400, 80 };
	newGameRect = { SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2, 100, 20 };
	hiscoresRect = { SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2 + 25, 100, 20 };
	instructionsRect = { SCREEN_WIDTH / 2 - 65, SCREEN_HEIGHT / 2 + 50, 130, 20 };
	quitRect = { SCREEN_WIDTH / 2 - 20, SCREEN_HEIGHT / 2 + 75, 40, 20 };

	selectedOption = NEW_GAME;
}

MainMenu::~MainMenu() {
}

void MainMenu::Tick(GamepadInput *gamepadInput) {
	ChangeSelectedOption(gamepadInput);
}

void MainMenu::ChangeSelectedOption(GamepadInput *gamepadInput) {

}

void MainMenu::Render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderCopy(renderer, logoTexture, NULL, &logoRect);
	SDL_RenderCopy(renderer, newGameTexture, NULL, &newGameRect);
	SDL_RenderCopy(renderer, hiscoresTexture, NULL, &hiscoresRect);
	SDL_RenderCopy(renderer, instructionsTexture, NULL, &instructionsRect);
	SDL_RenderCopy(renderer, quitTexture, NULL, &quitRect);
}

SDL_Texture* MainMenu::LoadTextTexture(std::string textureText, SDL_Color textColor) {
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);
	SDL_Texture *textTexture = NULL;
	if (textSurface == NULL) {
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	} else {
		textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		if (textTexture == NULL) {
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		} else {
			textTextureWidth = textSurface->w;
			textTextureHeight = textSurface->h;
		}

		SDL_FreeSurface(textSurface);
	}

	return textTexture;
}
