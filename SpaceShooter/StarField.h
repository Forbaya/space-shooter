#ifndef STARFIELD_H
#define STARTIELD_H

#include <vector>
#include "Star.h"

class StarField {
	public:
		StarField(int stars);
		void Render(SDL_Surface *screen);
		void Tick();
	private:
		std::vector<Star> stars;
};

#endif