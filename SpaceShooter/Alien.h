#ifndef ALIEN_H
#define ALIEN_H

#include <chrono>
#include <SDL_image.h>
#include <SDL.h>
#include <string>
#include <vector>
#include "Bullet.h"
#include "Entity.h"
#include "Vector2.h"

class Alien : public Entity {
	public:
		std::chrono::nanoseconds shotCooldown;
		std::chrono::nanoseconds noShotCooldown;
		std::chrono::nanoseconds shotCooldownLeft;
		std::vector<Bullet*> bullets;
		Time currentTime;
		Time previousTime;

		void Shoot(AxisInput *axisInput);
		std::vector<Bullet*> GetBullets();
};

#endif