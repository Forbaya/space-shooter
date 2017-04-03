#include "Asteroid.h"

Asteroid::Asteroid(int width, int height, SDL_Renderer *renderer) {
	using clock = std::chrono::high_resolution_clock;

	texture = LoadTexture("res/spritesheet.png", renderer);
	textureRegion = { 32, 0, width, height };
	center = { width / 2, height / 2 };
	
	RandomizeSpawnSpot(width, height);
	rotation = 0;
	health = 20;
	velocity = rand() % 10 + 1;

	currentTickTime = clock::now();
}

Asteroid::~Asteroid() {
}

void Asteroid::Move(int x, int y) {
	rect.x += x;
	rect.y += y;
}

void Asteroid::Tick(AxisInput * axisInput) {
	using clock = std::chrono::high_resolution_clock;

	previousTickTime = currentTickTime;
	currentTickTime = clock::now();
	auto deltaTime = currentTickTime - previousTickTime;

	if (passedAnimationTime >= animationLength) {
		rotation = fmod(rotation + 1.0, 360.0);
		passedAnimationTime -= animationLength;
	}

	Move(direction->GetX(), direction->GetY());
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
