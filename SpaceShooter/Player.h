#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include "Entity.h"

class Player : public Entity {
	public:
		Player(int, int);
		~Player();
		SDL_Rect GetRect();
		void Move(int x, int y);
		void Tick();
	private:
		SDL_Rect rect;
};

#endif