#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <SDL.h>

#include "Player.h"
#include "Game.h"
#include "AxisInput.h"

class InputHandler {
public:
	InputHandler();
	void HandleInput(SDL_Event e, Game *game);
	AxisInput* GetAxisInput();
private:
	void HandleControllerAxisInput(SDL_Event e);
	void HandleControllerButtonInput(SDL_Event e, Player *player);
	MovementSpeed MapAxisValueToMovementSpeed(int value);
	const int minimumAxisMovement = 3600;
	AxisInput *axisInput;
};

#endif