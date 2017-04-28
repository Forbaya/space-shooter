#ifndef ASTEROID_H
#define ASTEROID_H

#include <SDL.h>
#include "Constants.h"
#include "Entity.h"
#include "Vector2.h"

class Asteroid : public Entity {
	public:
		Asteroid(int width, int height, SDL_Renderer *renderer, Vector2 *textureRegion, long *gameScore);
		~Asteroid();
		void Move(int x, int y);
		void Tick(Inputs *inputs);
		void Render(SDL_Renderer *renderer);
		void RandomizeSpawnSpot(int width, int height);
		void SetCollision(bool collision);
		bool GetCollision();
		void SetDamage(int damage);
		bool GetDamage();
		Nanoseconds GetNextSpawnTime();
		bool IsDestroyable();
	private:
		Vector2 *direction;
		int velocity;
		bool collision;
		bool damage;
		Nanoseconds nextSpawnTime;
};

#endif