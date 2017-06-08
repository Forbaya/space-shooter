#ifndef ENTITY_H
#define ENTITY_H

#include <SDL_image.h>
#include <SDL.h>
#include <string>

#include "Cooldown.h"
#include "Inputs.h"
#include "Vector2.h"

class Entity {
	protected:
		SDL_Texture *texture;
		SDL_Rect textureRegion;
		SDL_Rect rect;
		SDL_Point center;
		double rotation;
		double rotationSpeed;
		Vector2 *position;
		Nanoseconds animationLength;
		Nanoseconds passedAnimationTime;
		Cooldown *immunity;
		Time currentTickTime;
		Time previousTickTime;
		int health;
		int reward;
	public:
		Entity(int width, int height, SDL_Renderer *renderer, Vector2 *textureRegion);
		~Entity();
		virtual void Tick(Inputs *inputs)=0;
		virtual void Move(int x, int y)=0;
		virtual void Render(SDL_Renderer *renderer)=0;

		SDL_Texture* LoadTexture(std::string path, SDL_Renderer *renderer);
		SDL_Rect GetRect();
		Vector2* GetPosition();
		int GetHealth();
		bool IsDead();
		void TakeDamage(int damage);
		bool IsImmune();
		void Rotate();
		int GetReward();
};

#endif
