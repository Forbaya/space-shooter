#include "HealthDrop.h"

HealthDrop::HealthDrop(int x, int y, int width, int height, SDL_Renderer *renderer, Vector2 *textureRegion) 
		: Entity(width, height, renderer, textureRegion) {
	healthAmount = 1;
	rotationSpeed = (double) rand();
	Rotate();
	currentFrame = 0;
	rect = { x, y, width, height };
	deletable = false;
	show = true;

	passedAnimationTime = zeroNanoseconds;
	currentFrameTime = zeroNanoseconds;
	frameTime = Nanoseconds(500000000);
	currentAliveTime = zeroNanoseconds;
	aliveTime = Nanoseconds(7000000000);
	blinkTime = zeroNanoseconds;
	blinkInterval = Nanoseconds(333333333);

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
	currentAliveTime += std::chrono::duration_cast<Nanoseconds>(deltaTime);
	
	if (currentFrameTime >= frameTime) {
		ChangeAnimationFrame();
		currentFrameTime -= frameTime;
	}

	if (currentAliveTime >= Nanoseconds(4000000000)) {
		blinkTime += std::chrono::duration_cast<Nanoseconds>(deltaTime);
		if (blinkTime >= blinkInterval) {
			show = show ? false : true;
			blinkTime -= blinkInterval;
		}
	}

	if (currentAliveTime >= aliveTime) {
		deletable = true;
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
	if (show) {
		SDL_RenderCopyEx(renderer, texture, &textureRegion, &rect, rotation, &center, SDL_FLIP_NONE);
	}
}

int HealthDrop::GetHealthAmount() {
	return healthAmount;
}

bool HealthDrop::GetDeletable() {
	return deletable;
}

void HealthDrop::SetDeletable(bool deletable) {
	this->deletable = deletable;
}

int HealthDrop::NextFrame() {
	int nextFrame = currentFrame;
	nextFrame++;
	
	return nextFrame >= 4 ? 0 : nextFrame;
}
