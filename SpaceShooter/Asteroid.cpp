#include "Asteroid.h"

Asteroid::Asteroid(int width, int height, SDL_Renderer *renderer, Vector2 *textureRegion) 
		: Entity(width, height, renderer, textureRegion) {
	RandomizeSpawnSpot(width, height);
	rotationSpeed = 1.0;
	health = 1;
	damage = 2;
	velocity = rand() % 9 + 1;
	collision = false;
	this->reward = 1;

	nextSpawnTime = Nanoseconds(300000000);

	currentTickTime = Clock::now();
}

Asteroid::~Asteroid() {
	SDL_DestroyTexture(texture);
	texture = NULL;

}

void Asteroid::Move(int x, int y) {
	rect.x += x;
	rect.y += y;
}

void Asteroid::Tick(Inputs *inputs) {
	previousTickTime = currentTickTime;
	currentTickTime = Clock::now();
	auto deltaTime = currentTickTime - previousTickTime;

	Rotate();

	Move(direction->GetX() * velocity, direction->GetY() * velocity);
}

void Asteroid::Render(SDL_Renderer *renderer) {
	SDL_RenderCopyEx(renderer, texture, &textureRegion, &rect, rotation, &center, SDL_FLIP_NONE);
}

void Asteroid::RandomizeSpawnSpot(int width, int height) {
	int border = rand() % 4;
	int x, y, directionX, directionY;
	if (border == TOP) {
		x = rand() % (SCREEN_WIDTH + 1);
		y = -32;
		directionX = rand() % 3 - 1;
		direction = new Vector2(directionX, 1);
	} else if (border == LEFT) {
		x = -32;
		y = rand() % (SCREEN_HEIGHT + 1);
		directionY = rand() % 3 - 1;
		direction = new Vector2(1, directionY);
	} else if (border == BOTTOM) {
		x = rand() % (SCREEN_WIDTH + 1);
		y = SCREEN_HEIGHT + 32;
		directionX = rand() % 3 - 1;
		direction = new Vector2(directionX, -1);
	} else {
		x = SCREEN_WIDTH + 32;
		y = rand() % (SCREEN_HEIGHT + 1);
		directionY = rand() % 3 - 1;
		direction = new Vector2(-1, directionY);
	}

	rect = { x, y, width, height };
}

void Asteroid::SetCollision(bool collision) {
	this->collision = collision;
}

bool Asteroid::GetCollision() {
	return collision;
}

void Asteroid::SetDamage(int damage) {
	this->damage = damage;
}

bool Asteroid::GetDamage() {
	return damage;
}

Nanoseconds Asteroid::GetNextSpawnTime() {
	return nextSpawnTime;
}

bool Asteroid::IsDestroyable() {
	return rect.x < -SCREEN_WIDTH * 3 || rect.x > SCREEN_WIDTH * 3 ||
			rect.y < -SCREEN_HEIGHT * 3 || rect.y > SCREEN_HEIGHT * 3 || IsDead();
}
