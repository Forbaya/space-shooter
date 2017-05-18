#include "Hiscores.h"

Hiscores::Hiscores(SDL_Renderer * renderer) {
	this->renderer = renderer;
	font = TTF_OpenFont("res/roboto.ttf", 24);
	white = { 255, 255, 255 };
	selectedColor = { 255, 255, 0 };
}

Hiscores::~Hiscores() {
}
