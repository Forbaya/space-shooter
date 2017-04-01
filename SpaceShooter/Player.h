#ifndef PLAYER_H
#define PLAYER_H

#include <chrono>
#include <SDL.h>
#include <vector>
#include "AxisInput.h"
#include "Bullet.h"
#include "Entity.h"
#include "Vector2.h"

class Player : public Entity {
	public:
		Player(int, int);
		~Player();
		SDL_Rect GetRect();
		void Move(int x, int y);
		void Tick(AxisInput *axisInput);
		void Shoot(AxisInput *axisInput);
		std::vector<Bullet*> GetBullets();
		void Render(SDL_Renderer *renderer);
		void LoadTexture(std::string path, SDL_Renderer *renderer);
		SDL_Texture* GetTexture();
	private:
		SDL_Rect rect;
		Vector2 *position;
		std::vector<Bullet*> bullets;
		std::chrono::nanoseconds shotCooldown;
		std::chrono::nanoseconds noShotCooldown;
		std::chrono::nanoseconds shotCooldownLeft;
		std::chrono::time_point<std::chrono::steady_clock, std::chrono::duration<__int64, std::ratio<1, 1000000000>>> currentTime;
		std::chrono::time_point<std::chrono::steady_clock, std::chrono::duration<__int64, std::ratio<1, 1000000000>>> previousTime;
		SDL_Texture *texture;
};

#endif