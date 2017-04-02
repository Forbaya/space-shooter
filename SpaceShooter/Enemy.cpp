#include <chrono>
#include <iostream>
#include "Constants.h"
#include "Enemy.h"

Enemy::Enemy(int width, int height) {
	using clock = std::chrono::high_resolution_clock;

	position = new Vector2(-32, 32);
	rect = {-32, 32, width, height};
	health = 10;

	movement = std::chrono::nanoseconds(0);
	movementCooldown = std::chrono::nanoseconds(100);

	currentTime = clock::now();
}

void Enemy::Tick(AxisInput * axisInput) {
	using clock = std::chrono::high_resolution_clock;

	previousTime = currentTime;
	currentTime = clock::now();
	auto deltaTime = currentTime - previousTime;
	movement += std::chrono::duration_cast<std::chrono::nanoseconds>(deltaTime);

	if (movement >= movementCooldown) {
		Move(1, 0);
		if (position->GetX() >= SCREEN_WIDTH + 32) {
			position->SetX(-32);
			rect.x = -32;
		}
		movement -= movementCooldown;
	}
	
}

void Enemy::Move(int x, int y) {
	rect.x += x;
	rect.y += y;
	position->SetX(position->GetX() + x);
	position->SetY(position->GetY() + y);
}

void Enemy::Render(SDL_Renderer *renderer) {
	SDL_SetRenderDrawColor(renderer, 255, 255, 0, 0);
	SDL_RenderFillRect(renderer, &rect);
}

SDL_Rect Enemy::GetRect() {
	return rect;
}

int Enemy::GetHealth() {
	return health;
}

void Enemy::SetHealth(int health) {
	this->health = health;
}
