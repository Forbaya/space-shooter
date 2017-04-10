#ifndef SCREEN_H
#define SCREEN_H

#include <SDL.h>
#include "GamepadInput.h"

class Screen {
	protected:
		bool running;
		int nextScreen;
	public:
		Screen();
		~Screen();
		virtual void Tick(GamepadInput *gamepadInput);
		virtual void Render();
		bool IsRunning();
		int GetNextScreen();
		void SetRunning(bool running);
		void SetNextScreen(int nextScreen);
};

#endif