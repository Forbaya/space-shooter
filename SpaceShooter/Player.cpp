#include "Player.h"

Player::Player(int width, int height, SDL_Renderer *renderer) {
	texture = LoadTexture("res/spritesheet.png", renderer);
	textureRegion = { 0, 0, width, height };
	rect = { SCREEN_WIDTH/2 - width, SCREEN_HEIGHT/2 - height, width, height };
	center = { width/2, height/2 };
	rotation = 0;
	rotationSpeed = 45.0;
	health = 3;

	shotCooldown = Nanoseconds(50000000);
	shotCooldownLeft = Nanoseconds(0);
	animationLength = Nanoseconds(100000000);
	passedAnimationTime = Nanoseconds(0);
	immunity = Nanoseconds(0);
	immunityLength = Nanoseconds(1000000000);

	currentTickTime = Clock::now();
}

Player::~Player() {
}

void Player::Tick(AxisInput *axisInput) {
	previousTickTime = currentTickTime;
	currentTickTime = Clock::now();
	auto deltaTime = currentTickTime - previousTickTime;
	immunity -= std::chrono::duration_cast<Nanoseconds>(deltaTime);
	shotCooldownLeft -= std::chrono::duration_cast<Nanoseconds>(deltaTime);
	passedAnimationTime += std::chrono::duration_cast<Nanoseconds>(deltaTime);
	
	Rotate();
	Shoot(axisInput);
	Move(axisInput->GetLeftX(), axisInput->GetLeftY());

	for (Bullet *bullet : bullets) {
		bullet->Tick(axisInput);
	}

	// Removes bullets that are far out of screen and bullets that hit something from the vector.
	bullets.erase(
		std::remove_if(
			bullets.begin(), bullets.end(),
			[](Bullet *bullet) {
				return bullet->GetRect().x < -SCREEN_WIDTH * 2 || bullet->GetRect().x > SCREEN_WIDTH * 2 ||
						bullet->GetRect().y < -SCREEN_HEIGHT * 2 || bullet->GetRect().y > SCREEN_HEIGHT * 2 || bullet->GetCollision();
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