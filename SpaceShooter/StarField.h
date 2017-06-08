#ifndef STARFIELD_H
#define STARTIELD_H

#include <vector>
#include "Inputs.h"
#include "Star.h"

class StarField {
	public:
		StarField(int stars);
		~StarField();
		void Render(SDL_Renderer *renderer);
		void Tick(Inputs *inputs);
	private:
		std::vector<Star*> stars;
};

#endif
