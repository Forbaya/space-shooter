#include "Star.h"

Star::Star(int x, int y, int size, int speed) {
	this->x = x;
	this->y = y;
	this->size = size;
	this->speed = speed;

	rect = { x, y, size, size };
}

Star::~Star() {
}

int Star::GetX() {
	return x;
}

int Star::GetY() {
	return y;
}

int Star::GetSize() {
	return size;
}

float Star::GetSpeed() {
	if (size == 2) {
		return STAR_MIDDLE_SPEED;
	}
	return size == 3 ? STAR_MAXIMUM_SPEED : STAR_MINIMUM_SPEED;
}

SDL_Rect Star::GetRect(){
	return rect;
}

void Star::Move(int x, int y) {
	this->x += x;
	this->y += y;
	rect.x += x;
	rect.y += y;
}

void Star::Tick(GamepadInput *gamepadInput) {
}

void Star::Render(SDL_Renderer *renderer) {
	SDL_RenderFillRect(renderer, &rect);
}
