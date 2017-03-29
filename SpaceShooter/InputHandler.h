#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <SDL.h>
#include "AxisInput.h"
#include "Game.h"
#include "Player.h"

class InputHandler {
	public:
		InputHandler();
		~InputHandler();
		void HandleInput(SDL_Event e, Game *game);
		AxisInput* GetAxisInput();
		int GetRightXValue();
		int GetRightYValue();
	private:
		void HandleControllerAxisInput(SDL_Event e);
		void HandleControllerButtonInput(SDL_Event e, Player *player);
		MovementSpeed MapAxisValueToMovementSpeed(int value);
		const int minimumAxisMovement = 3600;
		AxisInput *axisInput;
		int rightXValue;
		int rightYValue;
};

#endif