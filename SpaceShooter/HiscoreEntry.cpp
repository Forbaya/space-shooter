#include "HiscoreEntry.h"

HiscoreEntry::HiscoreEntry(SDL_Renderer *renderer, int rank, 
		std::string playerName, std::string date, std::string score) {
	this->renderer = renderer;
	this->rank = rank;

	font = TTF_OpenFont("res/roboto.ttf", 24);
	white = { 255, 255, 255 };
	gold = { 255, 233, 0 };
	silver = { 192, 192, 192 };
	bronze = { 205, 127, 50 };

	int playerNameLength = playerName.length();
	int rankDigits = CountDigitsInInteger(rank);
	int scoreLength = score.length();
	int y = 45 + (rank - 1) * 30;
	rankRect = { 30, y, 15 * rankDigits, 30 };
	playerNameRect = { 80, y, playerNameLength * 18, 30 };
	dateRect = { 380, y, 200, 30 };
	scoreRect = { 605, y, scoreLength * 15, 30 };

	SDL_Color rowColor;
	if (rank == 1) {
		rowColor = gold;
	} else if (rank == 2) {
		rowColor = silver;
	} else if (rank == 3) {
		rowColor = bronze;
	} else {
		rowColor = white;
	}

	rankTexture = LoadTextTexture(std::to_string(rank), rowColor, renderer);
	playerNameTexture = LoadTextTexture(playerName, rowColor, renderer);
	dateTexture = LoadTextTexture(date, rowColor, renderer);
	scoreTexture = LoadTextTexture(score, rowColor, renderer);
}

HiscoreEntry::~HiscoreEntry() {
	TTF_CloseFont(font);

	SDL_DestroyTexture(rankTexture);
	SDL_DestroyTexture(playerNameTexture);
	SDL_DestroyTexture(dateTexture);
	SDL_DestroyTexture(scoreTexture);

	rankTexture = NULL;
	playerNameTexture = NULL;
	dateTexture = NULL;
	scoreTexture = NULL;
}

void HiscoreEntry::Render() {
	SDL_RenderCopy(renderer, rankTexture, NULL, &rankRect);
	SDL_RenderCopy(renderer, playerNameTexture, NULL, &playerNameRect);
	SDL_RenderCopy(renderer, dateTexture, NULL, &dateRect);
	SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);
}

SDL_Texture* HiscoreEntry::LoadTextTexture(std::string text, SDL_Color textColor, SDL_Renderer *renderer) {
	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), textColor);
	SDL_Texture *texture = NULL;
	if (surface == NULL) {
		std::string error = TTF_GetError();
		if (error.compare("Text has zero width") != 0) {
			printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
		}
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

int HiscoreEntry::CountDigitsInInteger(int x) {
	int digits = 0;

	do {
		digits++;
		x /= 10;
	} while (x);

	return digits;
}