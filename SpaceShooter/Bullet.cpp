#include "Bullet.h"

Bullet::Bullet(Vector2 position, Vector2 direction, int size, int speed) {
	this->position = position;
	this->direction = direction;
	this->size = size;
	this->speed = speed;
}

Bullet::~Bullet() {
}

Vector2 Bullet::GetPosition() {
	return position;
}

Vector2 Bullet::GetDirection() {
	return direction;
}

int Bullet::GetSpeed() {
	return speed;
}

int Bullet::GetSize() {
	return size;
}

void Bullet::SetPosition(Vector2 position) {
	this->position = position;
}

void Bullet::GetSpeed(int speed) {
	this->speed = speed;
}

void Bullet::Tick() {
}

void Bullet::Move(int x, int y) {
}
