#include "Star.h"
#include "Constants.h"

Star::Star(int x, int y, int size, int speed) {
	this->x = x;
	this->y = y;
	this->size = size;
	this->speed = speed;

	rect.x = x;
	rect.y = y;
	rect.w = size;
	rect.h = size;
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

StarSpeed Star::GetSpeed() {
	if (size == 2) {
		return StarSpeed::STAR_MAXIXMUM_SPEED;
	}
	return size == 3 ? StarSpeed::STAR_MIDDLE_SPEED : StarSpeed::STAR_MAXIXMUM_SPEED;
}

SDL_Rect Star::GetRect(){
	return rect;
}
