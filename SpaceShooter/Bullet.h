#ifndef BULLET_H
#define BULLET_H

#include "Vector2.h"

class Bullet {
public:
	Bullet(Vector2 position, Vector2 direction, int size);
	Vector2 GetPosition();
	Vector2 GetDirection();
	int GetSize();
	void SetPosition(Vector2 position);
private:
	Vector2 position;
	Vector2 direction;
	int size;
};

#endif