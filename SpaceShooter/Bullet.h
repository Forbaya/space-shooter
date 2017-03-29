#ifndef BULLET_H
#define BULLET_H

#include "Entity.h"
#include "Vector2.h"

class Bullet : public Entity {
	public:
		Bullet(Vector2 position, Vector2 direction, int size, int speed);
		~Bullet();
		Vector2 GetPosition();
		Vector2 GetDirection();
		int GetSpeed();
		int GetSize();
		void SetPosition(Vector2 position);
		void GetSpeed(int speed);
		void Tick();
		void Move(int x, int y);
	private:
		Vector2 position;
		Vector2 direction;
		int size;
		int speed;
};

#endif