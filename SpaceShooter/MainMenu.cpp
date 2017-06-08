#include "MainMenu.h"

MainMenu::MainMenu(SDL_Renderer *renderer) : Screen() {
	this->renderer = renderer;
	selectedColor = { 255, 255, 0 };

	logoRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, 400, 80 };
	SDL_Rect newGameRect = { SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2, 100, 20 };
	SDL_Rect hiscoresRect = { SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2 + 25, 100, 20 };
	SDL_Rect instructionsRect = { SCREEN_WIDTH / 2 - 65, SCREEN_HEIGHT / 2 + 50, 130, 20 };
	//SDL_Rect optionsRect = { SCREEN_WIDTH / 2 - 40, SCREEN_HEIGHT / 2 + 75, 80, 20 };
	SDL_Rect quitRect = { SCREEN_WIDTH / 2 - 20, SCREEN_HEIGHT / 2 + 75, 40, 20 };
	
	logoTexture = LoadTextTexture("SPACE SHOOTER!", white, renderer);
	Button *newGameButton = new Button(NEW_GAME, renderer, "New Game", newGameRect, true);
	Button *hiscoresButton = new Button(HISCORES, renderer, "Hiscores", hiscoresRect, false);
	Button *instructionsButton = new Button(INSTRUCTIONS, renderer, "Instructions", instructionsRect, false);
	//Button *optionsButton = new Button(OPTIONS, renderer, "Options", optionsRect, false);
	Button *quitButton = new Button(QUIT, renderer, "Quit", quitRect, false);
	buttons.push_back(newGameButton);
	buttons.push_back(hiscoresButton);
	buttons.push_back(instructionsButton);
	//buttons.push_back(optionsButton);
	buttons.push_back(quitButton);

	optionSwapCooldown = new Cooldown(Nanoseconds(500000000), false);
	optionSelectCooldown = new Cooldown(Nanoseconds(500000000), true);

	currentTickTime = Clock::now();
}

MainMenu::~MainMenu() {
	for (auto it = buttons.begin(); it != buttons.end(); ++it) {
		delete *it;
	}
	buttons.clear();

	SDL_DestroyTexture(logoTexture);
	logoTexture = NULL;
}

void MainMenu::Tick(Inputs *inputs) {
	previousTickTime = currentTickTime;
	currentTickTime = Clock::now();
	auto deltaTime = currentTickTime - previousTickTime;
	optionSwapCooldown->Tick(std::chrono::duration_cast<Nanoseconds>(deltaTime));
	optionSelectCooldown->Tick(std::chrono::duration_cast<Nanoseconds>(deltaTime));

	ChangeSelectedOption(inputs);
	if (!optionSelectCooldown->OnCooldown()) {
		SelectOption(inputs);
	}
}

void MainMenu::ChangeSelectedOption(Inputs *inputs) {
	if (optionSwapCooldown->GetCooldownLeft() <= zeroNanoseconds && (inputs->GetGamepadInput()->GetLeftY() == 1 ||
			inputs->GetGamepadInput()->GetDpadDown() || inputs->GetKeyboardInput()->GetArrowDown())) {
		optionSwapCooldown->PutOnCooldown();
		int previousOption = selectedOption;
		selectedOption++;
		if (selectedOption >= 4) {
			selectedOption = NEW_GAME;
		}
		Button *previouslySelectedButton = buttons.at(previousOption);
		SDL_DestroyTexture(previouslySelectedButton->GetTexture());
		previouslySelectedButton->LoadTexture(previouslySelectedButton->GetText(), white);
		Button *currentlySelectedButton = buttons.at(selectedOption);
		SDL_DestroyTexture(currentlySelectedButton->GetTexture());
		currentlySelectedButton->LoadTexture(currentlySelectedButton->GetText(), selectedColor);
	} else if (optionSwapCooldown->GetCooldownLeft() <= zeroNanoseconds && (inputs->GetGamepadInput()->GetLeftY() == -1 ||
			inputs->GetGamepadInput()->GetDpadUp() || inputs->GetKeyboardInput()->GetArrowUp())) {
		optionSwapCooldown->PutOnCooldown();
		int previousOption = selectedOption;
		selectedOption--;
		if (selectedOption <= -1) {
			selectedOption = QUIT;
		}
		Button *previouslySelectedButton = buttons.at(previousOption);
		SDL_DestroyTexture(previouslySelectedButton->GetTexture());
		previouslySelectedButton->LoadTexture(previouslySelectedButton->GetText(), white);
		Button *currentlySelectedButton = buttons.at(selectedOption);
		SDL_DestroyTexture(currentlySelectedButton->GetTexture());
		currentlySelectedButton->LoadTexture(currentlySelectedButton->GetText(), selectedColor);
	}
}

void MainMenu::SelectOption(Inputs *inputs) {
	if (inputs->GetGamepadInput()->GetButtonA() || inputs->GetKeyboardInput()->GetButtonEnter()) {
		if (selectedOption == QUIT) {
			SetRunning(false);
		} else if (selectedOption == NEW_GAME) {
			SetNextScreen(GAME_SCREEN);
		} else if (selectedOption == HISCORES) {
			SetNextScreen(HISCORES_SCREEN);
		} else if (selectedOption == INSTRUCTIONS) {
			SetNextScreen(INSTRUCTIONS_SCREEN);
		}
	}
}

void MainMenu::Render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderCopy(renderer, logoTexture, NULL, &logoRect);
	for (Button *button : buttons) {
		button->Render();
	}
}
