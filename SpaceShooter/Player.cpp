#include "Player.h"

Player::Player(int width, int height, SDL_Renderer *renderer, Vector2 *textureRegion)
		: Alien(width, height, renderer, textureRegion) {
	rect = { SCREEN_WIDTH/2 - width, SCREEN_HEIGHT/2 - height, width, height };
	rotationSpeed = 45.0;
	health = 3;

	shotCooldown = Nanoseconds(100000000);
	shotCooldownLeft = zeroNanoseconds;
	animationLength = Nanoseconds(100000000);
	passedAnimationTime = zeroNanoseconds;
	immunity = zeroNanoseconds;
	immunityLength = Nanoseconds(1000000000);

	currentTickTime = Clock::now();
}

Player::~Player() {
	for (Bullet *bullet : GetBullets()) {
		delete bullet;
		bullet = NULL;
	}

	SDL_DestroyTexture(texture);
	texture = NULL;
}

void Player::Tick(GamepadInput *gamepadInput) {
	previousTickTime = currentTickTime;
	currentTickTime = Clock::now();
	auto deltaTime = currentTickTime - previousTickTime;
	immunity -= std::chrono::duration_cast<Nanoseconds>(deltaTime);
	shotCooldownLeft -= std::chrono::duration_cast<Nanoseconds>(deltaTime);
	passedAnimationTime += std::chrono::duration_cast<Nanoseconds>(deltaTime);
	
	Rotate();
	Shoot(gamepadInput);
	Move(gamepadInput->GetLeftX(), gamepadInput->GetLeftY());

	for (Bullet *bullet : bullets) {
		bullet->Tick(gamepadInput);
	}

	// Removes bullets that are far out of screen and bullets that hit something from the vector.
	bullets.erase(
		std::remove_if(
			bullets.begin(), bullets.end(),
			[&](Bullet *bullet) {
				bool destroyable = bullet->IsDestroyable();
				if (destroyable) delete bullet;
				return destroyable;
			}
		),
		bullets.end()
	);
}

void Player::Move(int x, int y) {
	rect.x += x;
	if (rect.x < 0) {
		rect.x = 0;
	}
	if (rect.x > SCREEN_WIDTH - rect.w) {
		rect.x = SCREEN_WIDTH - rect.w;
	}
	rect.y += y;
	if (rect.y < 0) {
		rect.y = 0;
	}
	if (rect.y > SCREEN_HEIGHT - rect.h) {
		rect.y = SCREEN_HEIGHT - rect.h;
	}
}

void Player::Render(SDL_Renderer *renderer) {
	for (Bullet *bullet : bullets) {
		bullet->Render(renderer);
	}

	IsImmune() ? SDL_SetTextureColorMod(texture, 255, 0, 0) : SDL_SetTextureColorMod(texture, 255, 255, 255);
	SDL_RenderCopyEx(renderer, texture, &textureRegion, &rect, rotation, &center, SDL_FLIP_NONE);
}

bool Player::IsDestroyable() {
	return IsDead();
}
