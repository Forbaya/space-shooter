#ifndef ENEMY_H
#define ENEMY_H

#include <chrono>
#include <SDL.h>
#include "AxisInput.h"
#include "Entity.h"
#include "Vector2.h"

class Enemy : public Entity {
	public:
		Enemy(int width, int height);
		void Tick(AxisInput *axisInput);
		void Move(int x, int y);
		void Render(SDL_Renderer *renderer);
		SDL_Rect GetRect();
		int GetHealth();
		void SetHealth(int health);
	private:
		Vector2 *position;
		SDL_Rect rect;
		std::chrono::nanoseconds movement;
		std::chrono::nanoseconds movementCooldown;
		std::chrono::time_point<std::chrono::steady_clock, std::chrono::duration<__int64, std::ratio<1, 1000000000>>> currentTime;
		std::chrono::time_point<std::chrono::steady_clock, std::chrono::duration<__int64, std::ratio<1, 1000000000>>> previousTime;
		int health;
		int damage;
};

#endif