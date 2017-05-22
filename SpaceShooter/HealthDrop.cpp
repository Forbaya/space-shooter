#include "HealthDrop.h"

HealthDrop::HealthDrop(int x, int y, int width, int height, SDL_Renderer *renderer, Vector2 *textureRegion) 
		: Entity(width, height, renderer, textureRegion) {
	healthAmount = 1;
	rotationSpeed = (double) rand();
	Rotate();
	currentFrame = 0;
	rect = { x, y, width, height };
	collision = false;

	passedAnimationTime = zeroNanoseconds;
	currentFrameTime = zeroNanoseconds;
	frameTime = Nanoseconds(500000000);

	currentTickTime = Clock::now();
}

HealthDrop::~HealthDrop() {

}

void HealthDrop::Tick(Inputs *inputs) {
	previousTickTime = currentTickTime;
	currentTickTime = Clock::now();
	auto deltaTime = currentTickTime - previousTickTime;

	passedAnimationTime += std::chrono::duration_cast<Nanoseconds>(deltaTime);
	currentFrameTime += std::chrono::duration_cast<Nanoseconds>(deltaTime);
	
	if (currentFrameTime >= frameTime) {
		ChangeAnimationFrame();
		currentFrameTime -= frameTime;
	}
}

void HealthDrop::Move(int x, int y) {
}

void HealthDrop::ChangeAnimationFrame() {
	int nextFrame = NextFrame();
	textureRegion = { 64 + 32 * nextFrame, 0, 32, 32 };
	currentFrame = nextFrame;
	
}

void HealthDrop::Render(SDL_Renderer *renderer) {
	SDL_RenderCopyEx(renderer, texture, &textureRegion, &rect, rotation, &center, SDL_FLIP_NONE);
}

int HealthDrop::GetHealthAmount() {
	return healthAmount;
}

bool HealthDrop::GetCollision() {
	return collision;
}

void HealthDrop::SetCollision(bool collision) {
	this->collision = collision;
}

int HealthDrop::NextFrame() {
	int nextFrame = currentFrame;
	nextFrame++;
	
	return nextFrame >= 4 ? 0 : nextFrame;
}
