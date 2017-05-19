#include "Screen.h"

Screen::Screen() {
	running = true;
	nextScreen = -1;
	font = TTF_OpenFont("res/roboto.ttf", 24);
	white = { 255, 255, 255 };
}

Screen::~Screen() {
	TTF_CloseFont(font);
	font = NULL;
}

void Screen::Tick(Inputs *inputs) {
}

void Screen::Render() {
}

bool Screen::IsRunning() {
	return running;
}

int Screen::GetNextScreen() {
	return nextScreen;
}

void Screen::SetRunning(bool running) {
	this->running = running;
}

void Screen::SetNextScreen(int nextScreen) {
	this->nextScreen = nextScreen;
}

SDL_Texture* Screen::LoadTextTexture(std::string text, SDL_Color textColor, SDL_Renderer *renderer) {
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