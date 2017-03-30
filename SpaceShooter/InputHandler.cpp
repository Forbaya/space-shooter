#include <iostream>
#include <SDL.h>
#include <stdio.h>
#include "AxisInput.h"
#include "Constants.h"
#include "InputHandler.h"
#include "Game.h"

InputHandler::InputHandler() {
	axisInput = new AxisInput();
}

InputHandler::~InputHandler() {
} 

void InputHandler::HandleInput(SDL_Event e, Game *game) {
	if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE) {
		game->Stop();
	}
	else if (e.type == SDL_CONTROLLERAXISMOTION) {
		HandleControllerAxisInput(e);
	}
	else if (e.type == SDL_CONTROLLERBUTTONDOWN) {
		//HandleControllerButtonInput(e, player);
	}
}

AxisInput* InputHandler::GetAxisInput() {
	return axisInput;
}

void InputHandler::HandleControllerAxisInput(SDL_Event e) {
	int value = e.caxis.value;
	MovementSpeed speed = MapAxisValueToMovementSpeed(value);
	int dir = value >= 0 ? 1 : -1;

	int testX = 0;
	int testY = 0;
	if (e.caxis.axis == SDL_CONTROLLER_AXIS_LEFTX) {
		axisInput->SetLeftX(speed * dir);
	} else if (e.caxis.axis == SDL_CONTROLLER_AXIS_LEFTY) {
		axisInput->SetLeftY(speed * dir);
	} else if (e.caxis.axis == SDL_CONTROLLER_AXIS_RIGHTX) {
		int rightX = value >= 3600 || value <= -3600 ? 1 * dir : 0;
		testX = rightX;
		axisInput->SetRightX(rightX);
	} else if (e.caxis.axis == SDL_CONTROLLER_AXIS_RIGHTY) {
		int rightY = value >= 15000 || value <= -15000 ? 1 * dir : 0;
		axisInput->SetRightY(rightY);
		testY = rightY;
	}
	//printf("x: %d\ty: %d\n", testX, testY);
}

void InputHandler::HandleControllerButtonInput(SDL_Event e, Player *player) {
	if (e.cbutton.button == SDL_CONTROLLER_BUTTON_A) {
		printf("A\n");
	}
	else if (e.cbutton.button == SDL_CONTROLLER_BUTTON_B) {
		printf("B\n");
	}
	else if (e.cbutton.button == SDL_CONTROLLER_BUTTON_X) {
		printf("X\n");
	}
	else if (e.cbutton.button == SDL_CONTROLLER_BUTTON_Y) {
		printf("Y\n");
	}
	else if (e.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_UP) {
		printf("UP\n");
	}
	else if (e.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_DOWN) {
		printf("DOWN\n");
	}
	else if (e.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_LEFT) {
		printf("LEFT\n");
	}
	else if (e.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_RIGHT) {
		printf("RIGHT\n");
	}
}

MovementSpeed InputHandler::MapAxisValueToMovementSpeed(int value) {
	if (value > 30000 || value < -30000) {
		return REALLY_FAST_SPEED;
	}
	if (value > 20000 || value < -20000) {
		return FAST_SPEED;
	}
	if (value > 10000 || value < -10000) {
		return AVERAGE_SPEED;
	}
	if (value > 5000 || value < -5000) {
		return SLOW_SPEED;
	}
	return NO_SPEED;
}
