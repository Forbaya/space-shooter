#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <SDL.h>
#include "GamepadInput.h"
#include "Game.h"
#include "Player.h"

class InputHandler {
	public:
		InputHandler();
		~InputHandler();
		void HandleInput(SDL_Event e, Game *game);
		GamepadInput* GetGamepadInput();
		int GetScreen();
		void SetScreen(int screen);
	private:
		void HandleGamepadAxisInput(SDL_Event e);
		void HandleGamepadButtonInput(SDL_Event e);
		MovementSpeed MapAxisValueToMovementSpeed(int value);
		GamepadInput *gamepadInput;
		int screen;
};

#endif