#ifndef STARFIELD_H
#define STARTIELD_H

#include <vector>
#include "GamepadInput.h"
#include "Star.h"

class StarField {
	public:
		StarField(int stars);
		~StarField();
		void Render(SDL_Renderer *renderer);
		void Tick(GamepadInput *gamepadInput);
	private:
		std::vector<Star*> stars;
};

#endif