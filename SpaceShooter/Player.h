#ifndef PLAYER_H
#define PLAYER_H

#include <algorithm>
#include <chrono>
#include <SDL.h>
#include <vector>
#include "Alien.h"
#include "GamepadInput.h"
#include "Bullet.h"
#include "Constants.h"
#include "Vector2.h"

class Player : public Alien {
	public:
		Player(int width, int height, SDL_Renderer *renderer, Vector2 *textureRegion, long *gameScore);
		~Player();
		void Move(int x, int y);
		void Tick(GamepadInput *gamepadInput);
		void Render(SDL_Renderer *renderer);
		bool IsDestroyable();
};

#endif