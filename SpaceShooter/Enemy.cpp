#include "Enemy.h"

Enemy::Enemy(int width, int height, SDL_Renderer *renderer, Vector2 *textureRegion) 
		: Alien(width, height, renderer, textureRegion) {
	SDL_SetTextureColorMod(texture, 255, 128, 255);

	rect = { -32, 32, width, height };
	rotationSpeed = 45.0;
	health = 10;
	damage = 1;

	animationLength = std::chrono::nanoseconds(100000000);
	passedAnimationTime = std::chrono::nanoseconds(0);
	immunity = std::chrono::nanoseconds(0);
	immunityLength = std::chrono::nanoseconds(1000000000);

	currentTickTime = Clock::now();
}

Enemy::~Enemy() {
	SDL_DestroyTexture(texture);
	texture = NULL;
}

void Enemy::Tick(GamepadInput *gamepadInput) {
	if (!IsDead()) {
		previousTickTime = currentTickTime;
		currentTickTime = Clock::now();
		auto deltaTime = currentTickTime - previousTickTime;
		immunity -= std::chrono::duration_cast<Nanoseconds>(deltaTime);
		passedAnimationTime += std::chrono::duration_cast<Nanoseconds>(deltaTime);
		
		Rotate();

		Move(1, 0);
	}
}

void Enemy::Move(int x, int y) {
	rect.x += x;
	rect.y += y;

	if (rect.x >= SCREEN_WIDTH + 32) {
		rect.x = -32;
	}
}

void Enemy::Render(SDL_Renderer *renderer) {
	if (!IsDead()) {
		IsImmune() ? SDL_SetTextureColorMod(texture, 255, 0, 0) : SDL_SetTextureColorMod(texture, 255, 128, 255);
		SDL_RenderCopyEx(renderer, texture, &textureRegion, &rect, rotation, &center, SDL_FLIP_NONE);
	}
}

int Enemy::GetHealth() {
	return health;
}

void Enemy::SetHealth(int health) {
	this->health = health;
}

bool Enemy::IsDestroyable() {
	return IsDead();
}
