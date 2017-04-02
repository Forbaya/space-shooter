#include "Player.h"

Player::Player(int width, int height, SDL_Renderer *renderer) {
	using clock = std::chrono::high_resolution_clock;

	texture = LoadTexture("res/spritesheet.png", renderer);
	position = new Vector2(SCREEN_WIDTH/2 - width, SCREEN_HEIGHT/2 - height);
	rect = {SCREEN_WIDTH/2 - width, SCREEN_HEIGHT/2 - height, width, height};
	center = { width/2, height/2 };
	rotation = 0;

	shotCooldown = std::chrono::nanoseconds(50000000);
	shotCooldownLeft = std::chrono::nanoseconds(0);
	noShotCooldown = std::chrono::nanoseconds(0);
	frameTime = std::chrono::nanoseconds(100000000);
	passedFrameTime = std::chrono::nanoseconds(0);

	currentFrameTime = clock::now();
}

Player::~Player() {
}

void Player::Tick(AxisInput *axisInput) {
	using clock = std::chrono::high_resolution_clock;

	previousFrameTime = currentFrameTime;
	currentFrameTime = clock::now();
	auto deltaTime = currentFrameTime - previousFrameTime;
	passedFrameTime += std::chrono::duration_cast<std::chrono::nanoseconds>(deltaTime);
	if (passedFrameTime >= frameTime) {
		rotation = fmod(rotation + 45.0, 360.0);
		passedFrameTime -= frameTime;
	}

	if (axisInput->GetRightX() != 0 || axisInput->GetRightY() != 0) {
		Shoot(axisInput);
	}

	Move(axisInput->GetLeftX(), axisInput->GetLeftY());

	for (Bullet *bullet : bullets) {
		bullet->Tick(axisInput);
	}

	bullets.erase(
		std::remove_if(
			bullets.begin(), bullets.end(),
			[](Bullet *bullet) {
				return bullet->GetPosition()->GetX() < -SCREEN_WIDTH * 2 || bullet->GetPosition()->GetX() > SCREEN_WIDTH * 2 ||
						bullet->GetPosition()->GetY() < -SCREEN_HEIGHT * 2 || bullet->GetPosition()->GetY() > SCREEN_HEIGHT * 2;
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

void Player::Shoot(AxisInput *axisInput) {
	if (shotCooldownLeft <= noShotCooldown) {
		Vector2 *direction = new Vector2(axisInput->GetRightX(), axisInput->GetRightY());
		int bulletSize = 6;
		Bullet *bullet = new Bullet(new Vector2(position->GetX() + rect.w/2 - bulletSize/2, position->GetY() + rect.h/2 - bulletSize/2), 
									new Vector2(direction->GetX(), direction->GetY()), bulletSize, 6);
		bullets.push_back(bullet);

		shotCooldownLeft = shotCooldown;
		currentTime = std::chrono::high_resolution_clock::now();
	} else {
		previousTime = currentTime;
		currentTime = std::chrono::high_resolution_clock::now();
		auto deltaTime = currentTime - previousTime;
		shotCooldownLeft -= std::chrono::duration_cast<std::chrono::nanoseconds>(deltaTime);
	}
}

void Player::Render(SDL_Renderer *renderer) {
	for (Bullet *bullet : bullets) {
		bullet->Render(renderer);
	}
	SDL_RenderCopyEx(renderer, texture, NULL, &rect, rotation, &center, SDL_FLIP_NONE);
}