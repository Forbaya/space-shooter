#ifndef STAR_H
#define STAR_H

#include <SDL.h>
#include "Constants.h"

class Star {
	public:
		Star(int x, int y, int size, int speed);
		~Star();
		int GetX();
		int GetY();
		int GetSize();
		StarSpeed GetSpeed();
		SDL_Rect GetRect();
	private:
		int x;
		int y;
		int size;
		int speed;
		SDL_Rect rect;
};

#endif