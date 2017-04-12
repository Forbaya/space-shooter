#ifndef SCREEN_H
#define SCREEN_H

#include <SDL.h>
#include "GamepadInput.h"
#include "KeyboardInput.h"

class Screen {
	protected:
		bool running;
		int nextScreen;
	public:
		Screen();
		~Screen();
		virtual void Tick(GamepadInput *gamepadInput, KeyboardInput *keyboardInput);
		virtual void Render();
		bool IsRunning();
		int GetNextScreen();
		void SetRunning(bool running);
		void SetNextScreen(int nextScreen);
};

#endif