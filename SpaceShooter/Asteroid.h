#ifndef ASTEROID_H
#define ASTEROID_H

#include <SDL.h>
#include "Constants.h"
#include "Entity.h"
#include "Vector2.h"

class Asteroid : public Entity {
	public:
		Asteroid(int width, int height, SDL_Renderer *renderer);
		~Asteroid();
		void Move(int x, int y);
		void Tick(AxisInput *axisInput);
		void Render(SDL_Renderer *renderer);
		void RandomizeSpawnSpot(int width, int height);
	private:
		Vector2 *direction;
		int velocity;
};

#endif