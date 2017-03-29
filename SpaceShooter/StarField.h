#ifndef STARFIELD_H
#define STARTIELD_H

#include <vector>
#include "AxisInput.h"
#include "Star.h"

class StarField {
	public:
		StarField(int stars);
		~StarField();
		void Render(SDL_Surface *screen);
		void Tick(AxisInput *axisInput);
	private:
		std::vector<Star*> stars;
};

#endif