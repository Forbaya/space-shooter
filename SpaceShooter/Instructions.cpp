#include "Instructions.h"

Instructions::Instructions(SDL_Renderer *renderer) : Screen() {
	this->renderer = renderer;

	std::string backText = "Back";
	int backTextLength = backText.length();
	SDL_Rect backButtonRect = { SCREEN_WIDTH / 2 - backTextLength / 2, SCREEN_HEIGHT - 100, 15 * backTextLength, 30 };
	backButton = new Button(BACK, renderer, backText, backButtonRect, true);

	std::string firstRowText = "Try to survive as long as you can, and get as many points as you can!";
	std::string secondRowText = "Controller inputs:";
	std::string thirdRowText = "- Left analog stick moves the player";
	std::string fourthRowText = "- Right analog stick shoots to the direction it's held";
	std::string fifthRowText = "- A-button selects a mode in the main menu and returns you back to main menu when dead";
	std::string sixthRowText = "- Start-button pauses when in game.";
	std::string seventhRowText = "Keyboard inputs:";
	std::string eighthRowText = "- WASD-keys move the player";
	std::string ninthRowText = "- Arrow-keys shoot to a direction";
	std::string tenthRowText = "- Enter selects a new game or quits when in main menu and returns you to main menu when dead";
	std::string eleventhRowText = "- You can't pause with keyboard yet.";

	int firstRowTextLength = firstRowText.length();
	int secondRowTextLength = secondRowText.length();
	int thirdRowTextLength = thirdRowText.length();
	int fourthRowTextLength = fourthRowText.length();
	int fifthRowTextLength = fifthRowText.length();
	int sixthRowTextLength = sixthRowText.length();
	int seventhRowTextLength = seventhRowText.length();
	int eighthRowTextLength = eighthRowText.length();
	int ninthRowTextLength = ninthRowText.length();
	int tenthRowTextLength = tenthRowText.length();
	int eleventhRowTextLength = eleventhRowText.length();

	firstRowRect = { 10, 10, 7 * firstRowTextLength, 18 };
	secondRowRect = { 10, 50, 7 * secondRowTextLength, 18 };
	thirdRowRect = { 15, 70, 7 * thirdRowTextLength, 18 };
	fourthRowRect = { 15, 90, 7 * fourthRowTextLength, 18 };
	fifthRowRect = { 15, 110, 7 * fifthRowTextLength, 18 };
	sixthRowRect = { 15, 130, 7 * sixthRowTextLength, 18 };
	seventhRowRect = { 10, 170, 7 * seventhRowTextLength, 18 };
	eighthRowRect = { 15, 190, 7 * eighthRowTextLength, 18 };
	ninthRowRect = { 15, 210, 7 * ninthRowTextLength, 18 };
	tenthRowRect = { 15, 230, 7 * tenthRowTextLength, 18 };
	eleventhRowRect = { 15, 250, 7 * eleventhRowTextLength, 18 };

	firstRowTexture = LoadTextTexture(firstRowText, white, renderer);
	secondRowTexture = LoadTextTexture(secondRowText, white, renderer);
	thirdRowTexture = LoadTextTexture(thirdRowText, white, renderer);
	fourthRowTexture = LoadTextTexture(fourthRowText, white, renderer);
	fifthRowTexture = LoadTextTexture(fifthRowText, white, renderer);
	sixthRowTexture = LoadTextTexture(sixthRowText, white, renderer);
	seventhRowTexture = LoadTextTexture(seventhRowText, white, renderer);
	eighthRowTexture = LoadTextTexture(eighthRowText, white, renderer);
	ninthRowTexture = LoadTextTexture(ninthRowText, white, renderer);
	tenthRowTexture = LoadTextTexture(tenthRowText, white, renderer);
	eleventhRowTexture = LoadTextTexture(eleventhRowText, white, renderer);

	optionSelectCooldown = Nanoseconds(500000000);
	optionSelectCooldownLeft = optionSelectCooldown;

	currentTickTime = Clock::now();
}

Instructions::~Instructions() {
	delete backButton;
	SDL_DestroyTexture(firstRowTexture);
	SDL_DestroyTexture(secondRowTexture);
	SDL_DestroyTexture(thirdRowTexture);
	SDL_DestroyTexture(fourthRowTexture);
	SDL_DestroyTexture(fifthRowTexture);
	SDL_DestroyTexture(sixthRowTexture);
	SDL_DestroyTexture(seventhRowTexture);
	SDL_DestroyTexture(eighthRowTexture);
	SDL_DestroyTexture(ninthRowTexture);
	SDL_DestroyTexture(tenthRowTexture);
	SDL_DestroyTexture(eleventhRowTexture);

	firstRowTexture = NULL;
	secondRowTexture = NULL;
	thirdRowTexture = NULL;
	fourthRowTexture = NULL;
	fifthRowTexture = NULL;
	sixthRowTexture = NULL;
	seventhRowTexture = NULL;
	eighthRowTexture = NULL;
	ninthRowTexture = NULL;
	tenthRowTexture = NULL;
	eleventhRowTexture = NULL;
}

void Instructions::Tick(Inputs *inputs) {
	previousTickTime = currentTickTime;
	currentTickTime = Clock::now();
	auto deltaTime = currentTickTime - previousTickTime;
	optionSelectCooldownLeft -= std::chrono::duration_cast<Nanoseconds>(deltaTime);

	if (optionSelectCooldownLeft <= zeroNanoseconds) {
		SelectOption(inputs);
	}
}

void Instructions::SelectOption(Inputs *inputs) {
	if (inputs->GetGamepadInput()->GetButtonA() || inputs->GetKeyboardInput()->GetButtonEnter()) {
		SetNextScreen(MAIN_MENU_SCREEN);
	}
}

void Instructions::Render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderCopy(renderer, firstRowTexture, NULL, &firstRowRect);
	SDL_RenderCopy(renderer, secondRowTexture, NULL, &secondRowRect);
	SDL_RenderCopy(renderer, thirdRowTexture, NULL, &thirdRowRect);
	SDL_RenderCopy(renderer, fourthRowTexture, NULL, &fourthRowRect);
	SDL_RenderCopy(renderer, fifthRowTexture, NULL, &fifthRowRect);
	SDL_RenderCopy(renderer, sixthRowTexture, NULL, &sixthRowRect);
	SDL_RenderCopy(renderer, seventhRowTexture, NULL, &seventhRowRect);
	SDL_RenderCopy(renderer, eighthRowTexture, NULL, &eighthRowRect);
	SDL_RenderCopy(renderer, ninthRowTexture, NULL, &ninthRowRect);
	SDL_RenderCopy(renderer, tenthRowTexture, NULL, &tenthRowRect);
	SDL_RenderCopy(renderer, eleventhRowTexture, NULL, &eleventhRowRect);
	backButton->Render();
}
