#include <SDL_image.h>
#include <SDL.h>
#include <chrono>
#include <iostream>
#include "Constants.h"
#include "Enemy.h"

Enemy::Enemy(int width, int height) {
	using clock = std::chrono::high_resolution_clock;

	position = new Vector2(-32, 32);
	rect = { -32, 32, width, height };
	center = { width / 2, height / 2 };
	health = 10;
	dead = false;

	immunity = std::chrono::nanoseconds(0);
	immunityLength = std::chrono::nanoseconds(100);

	currentTime = clock::now();
}

void Enemy::Tick(AxisInput * axisInput) {
	using clock = std::chrono::high_resolution_clock;

	previousTime = currentTime;
	currentTime = clock::now();
	auto deltaTime = currentTime - previousTime;
	immunity += std::chrono::duration_cast<std::chrono::nanoseconds>(deltaTime);

	Move(1, 0);
	if (position->GetX() >= SCREEN_WIDTH + 32) {
		position->SetX(-32);
		rect.x = -32;
	}	
}

void Enemy::Move(int x, int y) {
	rect.x += x;
	rect.y += y;
	position->SetX(position->GetX() + x);
	position->SetY(position->GetY() + y);
}

void Enemy::Render(SDL_Renderer *renderer) {
	if (!dead) {
		//SDL_SetRenderDrawColor(renderer, 255, 255, 0, 0);
		SDL_RenderCopyEx(renderer, texture, NULL, &rect, rotation, &center, SDL_FLIP_NONE);
	}
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

void Enemy::LoadTexture(std::string path, SDL_Renderer *renderer) {
	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) {
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else {
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 255, 255));
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL) {
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		SDL_FreeSurface(loadedSurface);
	}

	texture = newTexture;
}

SDL_Texture* Enemy::GetTexture() {
	return texture;
}
