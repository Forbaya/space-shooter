#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <SDL.h>
#include "GamepadInput.h"
#include "Game.h"
#include "Inputs.h"
#include "KeyboardInput.h"
#include "Player.h"

class InputHandler {
	public:
		InputHandler();
		~InputHandler();
		void HandleInput(SDL_Event e, Game *game);
		Inputs* GetInputs();
		int GetScreen();
		void SetScreen(int screen);
	private:
		void HandleKeyboardInput(SDL_Event e);
		void HandleGamepadAxisInput(SDL_Event e);
		void HandleGamepadButtonInput(SDL_Event e);
		MovementSpeed MapAxisValueToMovementSpeed(int value);
		Inputs *inputs;
		int screen;
};

#endif