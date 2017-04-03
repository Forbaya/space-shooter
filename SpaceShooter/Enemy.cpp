#include "Enemy.h"

Enemy::Enemy(int width, int height, SDL_Renderer *renderer) {
	using clock = std::chrono::high_resolution_clock;

	texture = Entity::LoadTexture("res/spritesheet.png", renderer);
	SDL_SetTextureColorMod(texture, 255, 128, 255);

	position = new Vector2(-32, 32);
	rect = { -32, 32, width, height };
	center = { width / 2, height / 2 };
	health = 10;
	damage = 1;

	zero = std::chrono::nanoseconds(0);
	animationLength = std::chrono::nanoseconds(100000000);
	passedAnimationTime = std::chrono::nanoseconds(0);
	immunity = std::chrono::nanoseconds(0);
	immunityLength = std::chrono::nanoseconds(1000000000);

	currentTickTime = clock::now();
}

void Enemy::Tick(AxisInput *axisInput) {
	if (!IsDead()) {
		using clock = std::chrono::high_resolution_clock;

		previousTickTime = currentTickTime;
		currentTickTime = clock::now();
		auto deltaTime = currentTickTime - previousTickTime;
		immunity -= std::chrono::duration_cast<std::chrono::nanoseconds>(deltaTime);
		passedAnimationTime += std::chrono::duration_cast<std::chrono::nanoseconds>(deltaTime);
		if (passedAnimationTime >= animationLength) {
			rotation = fmod(rotation + 45.0, 360.0);
			passedAnimationTime -= animationLength;
		}

		Move(1, 0);
		if (position->GetX() >= SCREEN_WIDTH + 32) {
			position->SetX(-32);
			rect.x = -32;
		}
	}
}

void Enemy::Move(int x, int y) {
	rect.x += x;
	rect.y += y;
	position->SetX(position->GetX() + x);
	position->SetY(position->GetY() + y);
}

void Enemy::Render(SDL_Renderer *renderer) {
	if (!IsDead()) {
		if (IsImmune()) {
			SDL_SetTextureColorMod(texture, 255, 0, 0);
		} else {
			SDL_SetTextureColorMod(texture, 255, 128, 255);
		}
		SDL_RenderCopyEx(renderer, texture, NULL, &rect, rotation, &center, SDL_FLIP_NONE);
	}
}

int Enemy::GetHealth() {
	return health;
}

void Enemy::SetHealth(int health) {
	this->health = health;
}