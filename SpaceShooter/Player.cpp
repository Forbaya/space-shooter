#include <chrono>
#include <SDL_image.h>
#include <SDL.h>
#include "AxisInput.h"
#include "Bullet.h"
#include "Constants.h"
#include "Player.h"
#include "InputHandler.h"

Player::Player(int width, int height) {
	position = new Vector2(SCREEN_WIDTH / 2 - 32, SCREEN_HEIGHT / 2 - 32);
	rect = {SCREEN_WIDTH / 2 - 32, SCREEN_HEIGHT / 2 - 32, 16, 16};

	shotCooldown = std::chrono::nanoseconds(50000000);
	shotCooldownLeft = std::chrono::nanoseconds(0);
	noShotCooldown = std::chrono::nanoseconds(0);
}

Player::~Player() {
}

SDL_Rect Player::GetRect() {
	return rect;
}

void Player::Tick(AxisInput *axisInput) {
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
	if (rect.x > SCREEN_WIDTH - 16) {
		rect.x = SCREEN_WIDTH - 16;
		position->SetX(SCREEN_WIDTH - 16);
	}
	rect.y += y;
	position->SetY(position->GetY() + y);
	if (rect.y < 0) {
		rect.y = 0;
		position->SetY(0);
	}
	if (rect.y > SCREEN_HEIGHT - 16) {
		rect.y = SCREEN_HEIGHT - 16;
		position->SetY(SCREEN_HEIGHT - 16);
	}
}

void Player::Shoot(AxisInput *axisInput) {
	if (shotCooldownLeft <= noShotCooldown) {
		Vector2 *direction = new Vector2(axisInput->GetRightX(), axisInput->GetRightY());
		Bullet *bullet = new Bullet(new Vector2(position->GetX(), position->GetY()), new Vector2(direction->GetX(), direction->GetY()), 5, 6);
		bullets.push_back(bullet);

		shotCooldownLeft = shotCooldown;
		currentTime = std::chrono::high_resolution_clock::now();
		bool kappa = true;
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
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void Player::LoadTexture(std::string path, SDL_Renderer *renderer) {
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) {
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	} else {
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL) {
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	texture = newTexture;
}

SDL_Texture* Player::GetTexture() {
	return texture;
}
