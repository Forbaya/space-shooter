#include "Player.h"

Player::Player(int width, int height, SDL_Renderer *renderer) {
	using clock = std::chrono::high_resolution_clock;

	texture = LoadTexture("res/spritesheet.png", renderer);
	position = new Vector2(SCREEN_WIDTH/2 - width, SCREEN_HEIGHT/2 - height);
	rect = { SCREEN_WIDTH/2 - width, SCREEN_HEIGHT/2 - height, width, height };
	center = { width/2, height/2 };
	rotation = 0;
	health = 3;

	zero = std::chrono::nanoseconds(0);
	shotCooldown = std::chrono::nanoseconds(50000000);
	shotCooldownLeft = std::chrono::nanoseconds(0);
	animationLength = std::chrono::nanoseconds(100000000);
	passedAnimationTime = std::chrono::nanoseconds(0);
	immunity = std::chrono::nanoseconds(0);
	immunityLength = std::chrono::nanoseconds(1000000000);

	currentTickTime = clock::now();
}

Player::~Player() {
}

void Player::Tick(AxisInput *axisInput) {
	using clock = std::chrono::high_resolution_clock;

	previousTickTime = currentTickTime;
	currentTickTime = clock::now();
	auto deltaTime = currentTickTime - previousTickTime;
	immunity -= std::chrono::duration_cast<std::chrono::nanoseconds>(deltaTime);
	shotCooldownLeft -= std::chrono::duration_cast<std::chrono::nanoseconds>(deltaTime);
	passedAnimationTime += std::chrono::duration_cast<std::chrono::nanoseconds>(deltaTime);
	if (passedAnimationTime >= animationLength) {
		rotation = fmod(rotation + 45.0, 360.0);
		passedAnimationTime -= animationLength;
	}

	if (axisInput->GetRightX() != 0 || axisInput->GetRightY() != 0) {
		Shoot(axisInput);
	}

	Move(axisInput->GetLeftX(), axisInput->GetLeftY());

	for (Bullet *bullet : bullets) {
		bullet->Tick(axisInput);
	}

	// Removes bullets that are far out of screen from the vector.
	bullets.erase(
		std::remove_if(
			bullets.begin(), bullets.end(),
			[](Bullet *bullet) {
				return bullet->GetPosition()->GetX() < -SCREEN_WIDTH * 2 || bullet->GetPosition()->GetX() > SCREEN_WIDTH * 2 ||
						bullet->GetPosition()->GetY() < -SCREEN_HEIGHT * 2 || bullet->GetPosition()->GetY() > SCREEN_HEIGHT * 2 || bullet->GetCollision();
			}),
		bullets.end());
}

void Player::Move(int x, int y) {
	rect.x += x;
	position->SetX(position->GetX() + x);
	if (rect.x < 0) {
		rect.x = 0;
		position->SetX(0);
	}
	if (rect.x > SCREEN_WIDTH - rect.w) {
		rect.x = SCREEN_WIDTH - rect.w;
		position->SetX(SCREEN_WIDTH - rect.w);
	}
	rect.y += y;
	position->SetY(position->GetY() + y);
	if (rect.y < 0) {
		rect.y = 0;
		position->SetY(0);
	}
	if (rect.y > SCREEN_HEIGHT - rect.h) {
		rect.y = SCREEN_HEIGHT - rect.h;
		position->SetY(SCREEN_HEIGHT - rect.h);
	}
}

void Player::Render(SDL_Renderer *renderer) {
	for (Bullet *bullet : bullets) {
		bullet->Render(renderer);
	}
	if (IsImmune()) {
		SDL_SetTextureColorMod(texture, 255, 0, 0);
	} else {
		SDL_SetTextureColorMod(texture, 255, 255, 255);
	}
	SDL_RenderCopyEx(renderer, texture, NULL, &rect, rotation, &center, SDL_FLIP_NONE);
}