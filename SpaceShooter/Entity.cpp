#include "Entity.h"

SDL_Texture* Entity::LoadTexture(std::string path, SDL_Renderer *renderer) {
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

	return newTexture;
}

SDL_Rect Entity::GetRect() {
	return rect;
}

Vector2* Entity::GetPosition() {
	return position;
}

int Entity::GetHealth() {
	return health;
}

bool Entity::IsDead() {
	return health <= 0;
}

void Entity::TakeDamage(int damage) {
	if (!IsImmune()) {
		health -= damage;
		immunity = immunityLength;
	}
}

bool Entity::IsImmune() {
	return immunity > zeroNanoseconds;
}

void Entity::Rotate() {
	if (passedAnimationTime >= animationLength) {
		rotation = fmod(rotation + rotationSpeed, 360.0);
		passedAnimationTime -= animationLength;
	}
}
