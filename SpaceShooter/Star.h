#ifndef STAR_H
#define STAR_H

#include <SDL.h>
#include "Constants.h"
#include "Entity.h"

class Star : public Entity {
	public:
		Star(int x, int y, int size, int speed);
		~Star();
		int GetX();
		int GetY();
		int GetSize();
		float GetSpeed();
		SDL_Rect GetRect();
		void Move(int x, int y);
		void Tick(AxisInput *axisInput);
		void Render(SDL_Renderer *renderer);
	private:
		int x;
		int y;
		int size;
		int speed;
};

#endif