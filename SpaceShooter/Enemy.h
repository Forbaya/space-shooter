#ifndef ENEMY_H
#define ENEMY_H

#include <chrono>
#include <SDL.h>
#include <string>
#include "Alien.h"
#include "Constants.h"
#include "Inputs.h"
#include "Vector2.h"

class Enemy : public Alien {
	public:
		Enemy(int width, int height, SDL_Renderer *renderer, Vector2 *textureRegion);
		~Enemy();
		void Tick(Inputs *inputs);
		void Move(int x, int y);
		void Render(SDL_Renderer *renderer);
		int GetHealth();
		void SetHealth(int health);
		bool IsDestroyable();
};

#endif
