#include "Vector2.h"

Vector2::Vector2(int xx, int yy) {
	x = xx;
	y = yy;
}

Vector2::Vector2() {
	x = 0;
	y = 0;
}

void Vector2::SetX(int x) {
	this->x = x;
}

void Vector2::SetY(int y) {
	this->y = y;
}

int Vector2::GetX() {
	return x;
}

int Vector2::GetY() {
	return y;
}
