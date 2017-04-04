#include "Asteroid.h"

Asteroid::Asteroid(int width, int height, SDL_Renderer *renderer) {
	texture = LoadTexture("res/spritesheet.png", renderer);
	textureRegion = { 32, 0, width, height };
	center = { width / 2, height / 2 };
	
	RandomizeSpawnSpot(width, height);
	rotation = 0;
	rotationSpeed = 1.0;
	health = 20;
	damage = 2;
	srand(time(NULL));
	velocity = rand() % 10 + 1;

	currentTickTime = Clock::now();
}

Asteroid::~Asteroid() {
}

void Asteroid::Move(int x, int y) {
	rect.x += x;
	rect.y += y;
}

void Asteroid::Tick(AxisInput *axisInput) {
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
	int x, y;
	if (border == TOP) {
		x = rand() % (SCREEN_WIDTH + 1);
		y = -32;
		direction = new Vector2(0, 1);
	} else if (border == LEFT) {
		x = -32;
		y = rand() % (SCREEN_HEIGHT + 1);
		direction = new Vector2(1, 0);
	} else if (border == BOTTOM) {
		x = rand() % (SCREEN_WIDTH + 1);
		y = SCREEN_HEIGHT + 32;
		direction = new Vector2(0, -1);
	} else {
		x = SCREEN_WIDTH + 32;
		y = rand() % (SCREEN_HEIGHT + 1);
		direction = new Vector2(-1, 0);
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
