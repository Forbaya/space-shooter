#include <chrono>
#include <SDL_image.h>
#include <SDL.h>
#include "AxisInput.h"
#include "Bullet.h"
#include "Constants.h"
#include "Player.h"
#include "InputHandler.h"

Player::Player(int width, int height) {
	using clock = std::chrono::high_resolution_clock;

	position = new Vector2(SCREEN_WIDTH/2 - 32, SCREEN_HEIGHT/2 - 32);
	rect = {SCREEN_WIDTH/2 - 32, SCREEN_HEIGHT/2 - 32, 32, 32};
	center = {rect.w/2, rect.h/2};
	rotation = 0;

	shotCooldown = std::chrono::nanoseconds(50000000);
	shotCooldownLeft = std::chrono::nanoseconds(0);
	noShotCooldown = std::chrono::nanoseconds(0);
	frameTime = std::chrono::nanoseconds(250000000);
	passedFrameTime = std::chrono::nanoseconds(0);

	currentFrameTime = clock::now();
}

Player::~Player() {
}

SDL_Rect Player::GetRect() {
	return rect;
}

void Player::Tick(AxisInput *axisInput) {
	using clock = std::chrono::high_resolution_clock;

	previousFrameTime = currentFrameTime;
	currentFrameTime = clock::now();
	auto deltaTime = currentFrameTime - previousFrameTime;
	passedFrameTime += std::chrono::duration_cast<std::chrono::nanoseconds>(deltaTime);
	if (passedFrameTime >= frameTime) {
		rotation = fmod(rotation + 90.0, 360.0);
		passedFrameTime -= frameTime;
	}

	if (axisInput->GetRightX() != 0 || axisInput->GetRightY() != 0) {
		Shoot(axisInput);
	}

	Move(axisInput->GetLeftX(), axisInput->GetLeftY());

	for (Bullet *bullet : bullets) {
		bullet->Tick(axisInput);
		//if (bullet->GetPosition()->GetX() < -SCREEN_WIDTH * 3 || bullet->GetPosition()->GetX() > SCREEN_WIDTH * 3 ||
		//	bullet->GetPosition()->GetY() < -SCREEN_HEIGHT * 3 || bullet->GetPosition()->GetY() > SCREEN_HEIGHT * 3) {
		//	bullets.remove
		//	delete bullet;
		//	
		//}
	}
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

std::vector<Bullet*> Player::GetBullets() {
	return bullets;
}

void Player::Render(SDL_Renderer *renderer) {
	for (Bullet *bullet : bullets) {
		bullet->Render(renderer);
	}
	SDL_RenderCopyEx(renderer, texture, NULL, &rect, rotation, &center, SDL_FLIP_NONE);
}

void Player::LoadTexture(std::string path, SDL_Renderer *renderer) {
	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) {
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	} else {
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 255, 255));
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL) {
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		SDL_FreeSurface(loadedSurface);
	}

	texture = newTexture;
}

SDL_Texture* Player::GetTexture() {
	return texture;
}
