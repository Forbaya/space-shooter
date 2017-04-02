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
		Player(int width, int height);
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
		Vector2 *position;
		SDL_Rect rect;
		SDL_Point center;
		std::vector<Bullet*> bullets;
		std::chrono::nanoseconds shotCooldown;
		std::chrono::nanoseconds noShotCooldown;
		std::chrono::nanoseconds shotCooldownLeft;
		std::chrono::nanoseconds frameTime;
		std::chrono::nanoseconds passedFrameTime;
		std::chrono::time_point<std::chrono::steady_clock, std::chrono::duration<__int64, std::ratio<1, 1000000000>>> currentTime;
		std::chrono::time_point<std::chrono::steady_clock, std::chrono::duration<__int64, std::ratio<1, 1000000000>>> previousTime;
		std::chrono::time_point<std::chrono::steady_clock, std::chrono::duration<__int64, std::ratio<1, 1000000000>>> currentFrameTime;
		std::chrono::time_point<std::chrono::steady_clock, std::chrono::duration<__int64, std::ratio<1, 1000000000>>> previousFrameTime;
		SDL_Texture *texture;
		double rotation;
};

#endif