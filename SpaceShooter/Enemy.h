#ifndef ENEMY_H
#define ENEMY_H

#include <chrono>
#include <SDL.h>
#include <string>
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
		void LoadTexture(std::string path, SDL_Renderer *renderer);
		SDL_Texture* GetTexture();
		SDL_Point center;
	private:
		Vector2 *position;
		SDL_Rect rect;
		std::chrono::nanoseconds immunity;
		std::chrono::nanoseconds immunityLength;
		std::chrono::time_point<std::chrono::steady_clock, std::chrono::duration<__int64, std::ratio<1, 1000000000>>> currentTime;
		std::chrono::time_point<std::chrono::steady_clock, std::chrono::duration<__int64, std::ratio<1, 1000000000>>> previousTime;
		int health;
		int damage;
		bool dead;
		SDL_Texture *texture;
		double rotation;
};

#endif