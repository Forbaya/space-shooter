#include "Bullet.h"

Bullet::Bullet(Vector2 position, Vector2 direction, int size) {
	this->position = position;
	this->direction = direction;
	this->size = size;
}

Vector2 Bullet::GetPosition() {
	return position;
}

Vector2 Bullet::GetDirection() {
	return direction;
}

int Bullet::GetSize() {
	return size;
}

void Bullet::SetPosition(Vector2 position) {
	this->position = position;
}
