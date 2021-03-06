#ifndef ALIEN_H
#define ALIEN_H

#include <chrono>
#include <SDL_image.h>
#include <SDL.h>
#include <string>
#include <vector>

#include "Bullet.h"
#include "Cooldown.h"
#include "Entity.h"
#include "Inputs.h"
#include "Vector2.h"

class Alien : public Entity {
	protected:
		Cooldown *shotCooldown;
		std::vector<Bullet*> bullets;
		int damage;
	public:
		Alien(int width, int height, SDL_Renderer *renderer, Vector2 *textureRegion);
		~Alien();
		void Shoot(Inputs *inputs);
		std::vector<Bullet*> GetBullets();
		void SetDamage(int damage);
		int GetDamage();
};

#endif
