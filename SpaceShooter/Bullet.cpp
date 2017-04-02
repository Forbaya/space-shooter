#include "Bullet.h"

Bullet::Bullet(Vector2 *position, Vector2 *direction, int size, int speed) {
	this->position = position;
	this->direction = direction;
	this->size = size;
	this->speed = speed;

	rect = {position->GetX(), position->GetY(), size, size};
}

Bullet::~Bullet() {
}

Vector2* Bullet::GetDirection() {
	return direction;
}

int Bullet::GetSpeed() {
	return speed;
}

int Bullet::GetSize() {
	return size;
}

void Bullet::SetPosition(Vector2 *position) {
	this->position = position;
}

void Bullet::GetSpeed(int speed) {
	this->speed = speed;
}

void Bullet::Tick(AxisInput *axisInput) {
	Move(direction->GetX(), direction->GetY());
}

void Bullet::Move(int x, int y) {
	position->SetX(position->GetX() + x * speed);
	position->SetY(position->GetY() + y * speed);
	rect.x = position->GetX() + x * speed;
	rect.y = position->GetY() + y * speed;
}

void Bullet::Render(SDL_Renderer *renderer) {
	SDL_SetRenderDrawColor(renderer, 236, 28, 31, 0);
	SDL_RenderFillRect(renderer, &rect);
}