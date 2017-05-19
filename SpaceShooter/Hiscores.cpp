#include "Hiscores.h"

Hiscores::Hiscores(SDL_Renderer *renderer, Database *database) : Screen() {
	this->renderer = renderer;
	this->database = database;

	selectedColor = { 255, 255, 0 };

	rankTextRect = { 30, 10, 15*1, 30 };
	playerNameTextRect = { 80, 10, 15*11, 30 };
	dateTextRect = { 380, 10, 15*4, 30 };
	scoreTextRect = { 605, 10, 15*5, 30 };
	rankTextTexture = LoadTextTexture("#", white, renderer);
	playerNameTextTexture = LoadTextTexture("Player name", white, renderer);
	dateTextTexture = LoadTextTexture("Date", white, renderer);
	scoreTextTexture = LoadTextTexture("Score", white, renderer);

	topTenHiscores = database->GetTopTenHiscores();

	PopulateHiscoreEntries();

	SDL_Rect backButtonRect = { 200, 400, 15 * 4, 30 };
	SDL_Rect resetHiscoresRect = { 300, 400, 15 * 14, 30 };
	Button *backButton = new Button(BACK, renderer, "Back", backButtonRect, true);
	Button *resetHiscoresButton = new Button(RESET_HISCORES, renderer, "Reset hiscores", resetHiscoresRect, false);
	buttons.push_back(backButton);
	buttons.push_back(resetHiscoresButton);

	optionSwapCooldown = Nanoseconds(500000000);
	optionSwapCooldownLeft = zeroNanoseconds;
	optionSelectCooldown = Nanoseconds(500000000);
	optionSelectCooldownLeft = optionSelectCooldown;

	currentTickTime = Clock::now();
}

Hiscores::~Hiscores() {
	for (auto it = buttons.begin(); it != buttons.end(); ++it) {
		delete *it;
	}
	buttons.clear();

	for (auto it = hiscoreEntries.begin(); it != hiscoreEntries.end(); ++it) {
		delete *it;
	}
	hiscoreEntries.clear();

	SDL_DestroyTexture(rankTextTexture);
	SDL_DestroyTexture(playerNameTextTexture);
	SDL_DestroyTexture(dateTextTexture);
	SDL_DestroyTexture(scoreTextTexture);

	rankTextTexture = NULL;
	playerNameTextTexture = NULL;
	dateTextTexture = NULL;
	scoreTextTexture = NULL;
}

void Hiscores::Tick(Inputs *inputs) {
	previousTickTime = currentTickTime;
	currentTickTime = Clock::now();
	auto deltaTime = currentTickTime - previousTickTime;
	optionSwapCooldownLeft -= std::chrono::duration_cast<Nanoseconds>(deltaTime);
	optionSelectCooldownLeft -= std::chrono::duration_cast<Nanoseconds>(deltaTime);

	ChangeSelectedOption(inputs);
	if (optionSelectCooldownLeft <= zeroNanoseconds) {
		SelectOption(inputs);
	}
}

void Hiscores::PopulateHiscoreEntries() {
	for (int rank = 0; rank < topTenHiscores.size(); rank++) {
		std::vector<std::string> row = topTenHiscores.at(rank);
		std::string playerName = row.at(1);
		std::string date = row.at(2);
		std::string score = row.at(3);

		HiscoreEntry *hiscoreEntry = new HiscoreEntry(renderer, rank + 1, playerName, date, score);
		hiscoreEntries.push_back(hiscoreEntry);
	}
}

void Hiscores::ChangeSelectedOption(Inputs *inputs) {
	if (optionSwapCooldownLeft <= zeroNanoseconds && (inputs->GetGamepadInput()->GetLeftX() == 1 ||
			inputs->GetGamepadInput()->GetDpadRight() || inputs->GetKeyboardInput()->GetArrowRight())) {
		optionSwapCooldownLeft = optionSwapCooldown;
		int previousOption = selectedOption;
		selectedOption++;
		if (selectedOption >= 2) {
			selectedOption = BACK;
		}
		Button *previouslySelectedButton = buttons.at(previousOption);
		SDL_DestroyTexture(previouslySelectedButton->GetTexture());
		previouslySelectedButton->LoadTexture(previouslySelectedButton->GetText(), white);
		Button *currentlySelectedButton = buttons.at(selectedOption);
		SDL_DestroyTexture(currentlySelectedButton->GetTexture());
		currentlySelectedButton->LoadTexture(currentlySelectedButton->GetText(), selectedColor);
	} else if (optionSwapCooldownLeft <= zeroNanoseconds && (inputs->GetGamepadInput()->GetLeftX() == -1 ||
			inputs->GetGamepadInput()->GetDpadLeft() || inputs->GetKeyboardInput()->GetArrowLeft())) {
		optionSwapCooldownLeft = optionSwapCooldown;
		int previousOption = selectedOption;
		selectedOption--;
		if (selectedOption <= -1) {
			selectedOption = RESET_HISCORES;
		}
		Button *previouslySelectedButton = buttons.at(previousOption);
		SDL_DestroyTexture(previouslySelectedButton->GetTexture());
		previouslySelectedButton->LoadTexture(previouslySelectedButton->GetText(), white);
		Button *currentlySelectedButton = buttons.at(selectedOption);
		SDL_DestroyTexture(currentlySelectedButton->GetTexture());
		currentlySelectedButton->LoadTexture(currentlySelectedButton->GetText(), selectedColor);
	}
}

void Hiscores::SelectOption(Inputs *inputs) {
	if (inputs->GetGamepadInput()->GetButtonA() || inputs->GetKeyboardInput()->GetButtonEnter()) {
		if (selectedOption == BACK) {
			SetNextScreen(MAIN_MENU_SCREEN);
		} else if (selectedOption == RESET_HISCORES) {
			database->ResetHiscoreTable();

			topTenHiscores = database->GetTopTenHiscores();
			hiscoreEntries.clear();
			PopulateHiscoreEntries();
		}
	}
}

void Hiscores::Render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	for (HiscoreEntry *entry : hiscoreEntries) {
		entry->Render();
	}
	SDL_RenderCopy(renderer, rankTextTexture, NULL, &rankTextRect);
	SDL_RenderCopy(renderer, playerNameTextTexture, NULL, &playerNameTextRect);
	SDL_RenderCopy(renderer, dateTextTexture, NULL, &dateTextRect);
	SDL_RenderCopy(renderer, scoreTextTexture, NULL, &scoreTextRect);

	for (Button *button : buttons) {
		button->Render();
	}
} 