#ifndef ENEMY_H
#define ENEMY_H

#include <chrono>
#include <SDL.h>
#include <string>
#include "Alien.h"
#include "AxisInput.h"
#include "Constants.h"
#include "Vector2.h"

class Enemy : public Alien {
	public:
		Enemy(int width, int height, SDL_Renderer *renderer);
		~Enemy();
		void Tick(AxisInput *axisInput);
		void Move(int x, int y);
		void Render(SDL_Renderer *renderer);
		int GetHealth();
		void SetHealth(int health);
		bool IsDestroyable();
};

#endif