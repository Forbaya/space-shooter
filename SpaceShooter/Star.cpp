#include "Star.h"
#include "Constants.h"

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
		return STAR_MAXIXMUM_SPEED;
	}
	return size == 3 ? STAR_MIDDLE_SPEED : STAR_MAXIXMUM_SPEED;
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

void Star::Tick(AxisInput *axisInput) {
}
