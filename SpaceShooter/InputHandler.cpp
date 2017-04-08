#include "InputHandler.h"

InputHandler::InputHandler() {
	gamepadInput = new GamepadInput();
	screen = MAIN_MENU_SCREEN;
}

InputHandler::~InputHandler() {
} 

void InputHandler::HandleInput(SDL_Event e, Game *game) {
	if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE) {
		game->Stop();
	}
	else if (e.type == SDL_CONTROLLERAXISMOTION) {
		HandleGamepadAxisInput(e);
	}
	else if (e.type == SDL_CONTROLLERBUTTONDOWN) {
		HandleGamepadButtonInput(e);
	}
}

GamepadInput* InputHandler::GetGamepadInput() {
	return gamepadInput;
}

int InputHandler::GetScreen() {
	return screen;
}

void InputHandler::SetScreen(int screen) {
	this->screen = screen;
}

void InputHandler::HandleGamepadAxisInput(SDL_Event e) {
	int value = e.caxis.value;
	MovementSpeed speed = MapAxisValueToMovementSpeed(value);
	int dir = value >= 0 ? 1 : -1;

	if (screen == MAIN_MENU_SCREEN) {
		if (e.caxis.axis == SDL_CONTROLLER_AXIS_LEFTY && (value >= 3600 || value <= -3600)) {
			gamepadInput->SetLeftY(dir);
		}
		else {
			gamepadInput->SetLeftY(0);
		}
	} else if (screen == GAME_SCREEN) {
		if (e.caxis.axis == SDL_CONTROLLER_AXIS_LEFTX) {
			gamepadInput->SetLeftX(speed * dir);
		} else if (e.caxis.axis == SDL_CONTROLLER_AXIS_LEFTY) {
			gamepadInput->SetLeftY(speed * dir);
		} else if (e.caxis.axis == SDL_CONTROLLER_AXIS_RIGHTX) {
			int rightX = value >= 3600 || value <= -3600 ? 1 * dir : 0;
			gamepadInput->SetRightX(rightX);
		} else if (e.caxis.axis == SDL_CONTROLLER_AXIS_RIGHTY) {
			int rightY = value >= 15000 || value <= -15000 ? 1 * dir : 0;
			gamepadInput->SetRightY(rightY);
		}
	}
	
}

void InputHandler::HandleGamepadButtonInput(SDL_Event e) {
	if (e.cbutton.button == SDL_CONTROLLER_BUTTON_A) {
		gamepadInput->SetButtonA(true);
	}
	else if (e.cbutton.button == SDL_CONTROLLER_BUTTON_B) {
		gamepadInput->SetButtonB(true);
	}
	else if (e.cbutton.button == SDL_CONTROLLER_BUTTON_X) {
		gamepadInput->SetButtonX(true);
	}
	else if (e.cbutton.button == SDL_CONTROLLER_BUTTON_Y) {
		gamepadInput->SetButtonY(true);
	}
	else if (e.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_UP) {
	}
	else if (e.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_DOWN) {
	}
	else if (e.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_LEFT) {
	}
	else if (e.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_RIGHT) {
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
