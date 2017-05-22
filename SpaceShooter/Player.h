#ifndef PLAYER_H
#define PLAYER_H

#include <algorithm>
#include <chrono>
#include <SDL.h>
#include <vector>
#include "Alien.h"
#include "Bullet.h"
#include "Constants.h"
#include "Inputs.h"
#include "Vector2.h"

class Player : public Alien {
	public:
		Player(int width, int height, SDL_Renderer *renderer, Vector2 *textureRegion);
		~Player();
		void Move(int x, int y);
		void Tick(Inputs *inputs);
		std::pair<int, int> GetMovement(Inputs *inputs);
		void Render(SDL_Renderer *renderer);
		bool IsDestroyable();
		void RegenHealth(int amount);
	private:
		int maxHealth;
};

#endif