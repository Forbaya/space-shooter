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
		Nanoseconds shotCooldown;
		Nanoseconds shotCooldownLeft;
		std::vector<Bullet*> bullets;
		int damage;

		void Shoot(GamepadInput *gamepadInput);
		std::vector<Bullet*> GetBullets();
		void SetDamage(int damage);
		int GetDamage();
};

#endif