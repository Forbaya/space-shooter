#include "Button.h"


Button::Button(int buttonId, SDL_Renderer *renderer, std::string text, SDL_Rect rect, bool selected) {
	white = { 255, 255, 255 };
	selectedColor = { 255, 255, 0 };
	font = TTF_OpenFont("res/roboto.ttf", 24);

	this->buttonId = buttonId;
	this->renderer = renderer;
	this->text = text;
	this->color = selected ? selectedColor : white;
	this->rect = rect;
	this->selected = selected;
	LoadTexture(text, color);
}

Button::~Button() {
	TTF_CloseFont(font);
	SDL_DestroyTexture(texture);

	font = NULL;
	texture = NULL;
}

SDL_Texture* Button::GetTexture() {
	return texture;
}

void Button::LoadTexture(std::string text, SDL_Color textColor) {
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

	this->texture = texture;
}

void Button::Render() {
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}

std::string Button::GetText() {
	return text;
}
