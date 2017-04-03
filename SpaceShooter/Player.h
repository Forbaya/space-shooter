#ifndef PLAYER_H
#define PLAYER_H

#include <algorithm>
#include <chrono>
#include <SDL.h>
#include <vector>
#include "Alien.h"
#include "AxisInput.h"
#include "Bullet.h"
#include "Constants.h"
#include "Vector2.h"

class Player : public Alien {
	public:
		Player(int width, int height, SDL_Renderer *renderer);
		~Player();
		void Move(int x, int y);
		void Tick(AxisInput *axisInput);
		void Render(SDL_Renderer *renderer);
};

#endif