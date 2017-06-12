#include "Vector2.h"

Vector2::Vector2(int x, int y) {
	this->x = x;
	this->y = y;
}

Vector2::Vector2() {
	x = 0;
	y = 0;
}

Vector2::~Vector2() {
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

Vector2 Vector2::operator-(const Vector2 &v) {
	x -= v.x;
	y -= v.y;

	return Vector2(*this);
}

Vector2 Vector2::operator*(const double &v) {
	x *= v;
	y *= v;

	return Vector2(*this);
}

void Vector2::Normalize() {
	double length = sqrt(x*x + y*y);
	x = x / length;
	y = y / length;
}
