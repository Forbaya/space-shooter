#include "MainMenu.h"

MainMenu::MainMenu(SDL_Renderer *renderer) {
	this->renderer = renderer;
	font = TTF_OpenFont("res/roboto.ttf", 24);
	white = { 255, 255, 255 };
	selectedColor = { 255, 255, 0 };

	logoRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, 400, 80 };
	SDL_Rect newGameRect = { SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2, 100, 20 };
	SDL_Rect hiscoresRect = { SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2 + 25, 100, 20 };
	SDL_Rect instructionsRect = { SCREEN_WIDTH / 2 - 65, SCREEN_HEIGHT / 2 + 50, 130, 20 };
	SDL_Rect optionsRect = { SCREEN_WIDTH / 2 - 40, SCREEN_HEIGHT / 2 + 75, 80, 20 };
	SDL_Rect quitRect = { SCREEN_WIDTH / 2 - 20, SCREEN_HEIGHT / 2 + 100, 40, 20 };
	
	logoTexture = LoadTextTexture("SPACE SHOOTER!", white, renderer);
	Button *newGameButton = new Button(NEW_GAME, renderer, "New Game", newGameRect, true);
	Button *hiscoresButton = new Button(HISCORES, renderer, "Hiscores", hiscoresRect, false);
	Button *instructionsButton = new Button(INSTRUCTIONS, renderer, "Instructions", instructionsRect, false);
	Button *optionsButton = new Button(OPTIONS, renderer, "Options", optionsRect, false);
	Button *quitButton = new Button(QUIT, renderer, "Quit", quitRect, false);
	buttons.push_back(newGameButton);
	buttons.push_back(hiscoresButton);
	buttons.push_back(instructionsButton);
	buttons.push_back(optionsButton);
	buttons.push_back(quitButton);

	optionSwapCooldown = Nanoseconds(500000000);
	optionSwapCooldownLeft = zeroNanoseconds;

	currentTickTime = Clock::now();
}

MainMenu::~MainMenu() {
}

void MainMenu::Tick(GamepadInput *gamepadInput) {
	previousTickTime = currentTickTime;
	currentTickTime = Clock::now();
	auto deltaTime = currentTickTime - previousTickTime;
	optionSwapCooldownLeft -= std::chrono::duration_cast<Nanoseconds>(deltaTime);

	ChangeSelectedOption(gamepadInput);
}

void MainMenu::ChangeSelectedOption(GamepadInput *gamepadInput) {
	if (optionSwapCooldownLeft <= zeroNanoseconds && gamepadInput->GetLeftY() == 1) {
		optionSwapCooldownLeft = optionSwapCooldown;
		int previousOption = selectedOption;
		selectedOption++;
		if (selectedOption >= 5) {
			selectedOption = NEW_GAME;
		}
		Button *previouslySelectedButton = buttons.at(previousOption);
		previouslySelectedButton->LoadTexture(previouslySelectedButton->GetText(), white);
		Button *currentlySelectedButton = buttons.at(selectedOption);
		currentlySelectedButton->LoadTexture(currentlySelectedButton->GetText(), selectedColor);
	} else if (optionSwapCooldownLeft <= zeroNanoseconds && gamepadInput->GetLeftY() == -1) {
		optionSwapCooldownLeft = optionSwapCooldown;
		int previousOption = selectedOption;
		selectedOption--;
		if (selectedOption <= -1) {
			selectedOption = QUIT;
		}
		Button *previouslySelectedButton = buttons.at(previousOption);
		previouslySelectedButton->LoadTexture(previouslySelectedButton->GetText(), white);
		Button *currentlySelectedButton = buttons.at(selectedOption);
		currentlySelectedButton->LoadTexture(currentlySelectedButton->GetText(), selectedColor);
	}
}

SDL_Texture* MainMenu::LoadTextTexture(std::string text, SDL_Color textColor, SDL_Renderer *renderer) {
	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), textColor);
	SDL_Texture *texture = NULL;
	if (surface == NULL) {
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else {
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		if (texture == NULL) {
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}

		SDL_FreeSurface(surface);
	}

	return texture;
}

void MainMenu::Render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderCopy(renderer, logoTexture, NULL, &logoRect);
	for (Button *button : buttons) {
		button->Render();
	}
}
