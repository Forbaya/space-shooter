#ifndef SCREEN_H
#define SCREEN_H

#include <SDL.h>
#include "GamepadInput.h"

class Screen {
	public:
		virtual void Tick(GamepadInput *gamepadInput);
		virtual void Render();
};

#endif