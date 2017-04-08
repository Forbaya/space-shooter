#ifndef BULLET_H
#define BULLET_H

#include <SDL.h>
#include "GamepadInput.h"
#include "Entity.h"
#include "Vector2.h"

class Bullet : public Entity {
	public:
		Bullet(Vector2 *position, Vector2 *direction, int size, int speed, int damage);
		~Bullet();
		Vector2* GetDirection();
		int GetSpeed();
		int GetSize();
		void SetPosition(Vector2 *position);
		void GetSpeed(int speed);
		void Tick(GamepadInput *gamepadInput);
		void Move(int x, int y);
		void Render(SDL_Renderer *renderer);
		int GetDamage();
		void SetDamage(int damage);
		void SetCollision(bool collision);
		bool GetCollision();
		bool IsDestroyable();
	private:
		Vector2 *direction;
		int size;
		int speed;
		int damage;
		bool collision;
};

#endif