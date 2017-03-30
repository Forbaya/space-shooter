#ifndef PLAYER_H
#define PLAYER_H

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
		void Render(SDL_Surface *screen);
	private:
		SDL_Rect rect;
		Vector2 *position;
		std::vector<Bullet*> bullets;
};

#endif