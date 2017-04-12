#include "InputHandler.h"

InputHandler::InputHandler() {
	gamepadInput = new GamepadInput();
	keyboardInput = new KeyboardInput();
	screen = MAIN_MENU_SCREEN;
}

InputHandler::~InputHandler() {
}

void InputHandler::HandleInput(SDL_Event e, Game *game) {
	if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE) {
	} else if (e.type == SDL_CONTROLLERAXISMOTION) {
		HandleGamepadAxisInput(e);
	} else if (e.type == SDL_CONTROLLERBUTTONDOWN || e.type == SDL_CONTROLLERBUTTONUP) {
		HandleGamepadButtonInput(e);
	} else if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) {
		HandleKeyboardInput(e);
	}
}

GamepadInput* InputHandler::GetGamepadInput() {
	return gamepadInput;
}

KeyboardInput* InputHandler::GetKeyboardInput() {
	return keyboardInput;
}

int InputHandler::GetScreen() {
	return screen;
}

void InputHandler::SetScreen(int screen) {
	this->screen = screen;
}

void InputHandler::HandleKeyboardInput(SDL_Event e) {
	if (e.type == SDL_KEYDOWN) {
		if (e.key.keysym.sym == SDLK_w) {
			keyboardInput->SetButtonW(true);
		} else if (e.key.keysym.sym == SDLK_a) {
			keyboardInput->SetButtonA(true);
		} else if (e.key.keysym.sym == SDLK_s) {
			keyboardInput->SetButtonS(true);
		} else if (e.key.keysym.sym == SDLK_d) {
			keyboardInput->SetButtonD(true);
		} else if (e.key.keysym.sym == SDLK_UP) {
			keyboardInput->SetArrowUp(true);
		} else if (e.key.keysym.sym == SDLK_RIGHT) {
			keyboardInput->SetArrowRight(true);
		} else if (e.key.keysym.sym == SDLK_DOWN) {
			keyboardInput->SetArrowDown(true);
		} else if (e.key.keysym.sym == SDLK_LEFT) {
			keyboardInput->SetArrowLeft(true);
		} else if (e.key.keysym.sym == SDLK_RETURN) {
			keyboardInput->SetButtonEnter(true);
		}
	} else {
		if (e.key.keysym.sym == SDLK_w) {
			keyboardInput->SetButtonW(false);
		} else if (e.key.keysym.sym == SDLK_a) {
			keyboardInput->SetButtonA(false);
		} else if (e.key.keysym.sym == SDLK_s) {
			keyboardInput->SetButtonS(false);
		} else if (e.key.keysym.sym == SDLK_d) {
			keyboardInput->SetButtonD(false);
		} else if (e.key.keysym.sym == SDLK_UP) {
			keyboardInput->SetArrowUp(false);
		} else if (e.key.keysym.sym == SDLK_RIGHT) {
			keyboardInput->SetArrowRight(false);
		} else if (e.key.keysym.sym == SDLK_DOWN) {
			keyboardInput->SetArrowDown(false);
		} else if (e.key.keysym.sym == SDLK_LEFT) {
			keyboardInput->SetArrowLeft(false);
		} else if (e.key.keysym.sym == SDLK_RETURN) {
			keyboardInput->SetButtonEnter(false);
		}
	}
}

void InputHandler::HandleGamepadAxisInput(SDL_Event e) {
	int value = e.caxis.value;
	MovementSpeed speed = MapAxisValueToMovementSpeed(value);
	int dir = value >= 0 ? 1 : -1;

	if (screen == MAIN_MENU_SCREEN) {
		if (e.caxis.axis == SDL_CONTROLLER_AXIS_LEFTY && (value >= 8000 || value <= -8000)) {
			gamepadInput->SetLeftY(dir);
		} else {
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
	if (e.type == SDL_CONTROLLERBUTTONDOWN) {
		if (e.cbutton.button == SDL_CONTROLLER_BUTTON_A) {
			gamepadInput->SetButtonA(true);
		} else if (e.cbutton.button == SDL_CONTROLLER_BUTTON_B) {
			gamepadInput->SetButtonB(true);
		} else if (e.cbutton.button == SDL_CONTROLLER_BUTTON_X) {
			gamepadInput->SetButtonX(true);
		} else if (e.cbutton.button == SDL_CONTROLLER_BUTTON_Y) {
			gamepadInput->SetButtonY(true);
		} else if (e.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_UP) {
			gamepadInput->SetDpadUp(true);
		} else if (e.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_RIGHT) {
			gamepadInput->SetDpadRight(true);
		} else if (e.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_DOWN) {
			gamepadInput->SetDpadDown(true);
		} else if (e.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_LEFT) {
			gamepadInput->SetDpadLeft(true);
		} else if (e.cbutton.button == SDL_CONTROLLER_BUTTON_START) {
			gamepadInput->TogglePause();
		}
	} else {
		if (e.cbutton.button == SDL_CONTROLLER_BUTTON_A) {
			gamepadInput->SetButtonA(false);
		} else if (e.cbutton.button == SDL_CONTROLLER_BUTTON_B) {
			gamepadInput->SetButtonB(false);
		} else if (e.cbutton.button == SDL_CONTROLLER_BUTTON_X) {
			gamepadInput->SetButtonX(false);
		} else if (e.cbutton.button == SDL_CONTROLLER_BUTTON_Y) {
			gamepadInput->SetButtonY(false);
		} else if (e.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_UP) {
			gamepadInput->SetDpadUp(false);
		} else if (e.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_RIGHT) {
			gamepadInput->SetDpadRight(false);
		} else if (e.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_DOWN) {
			gamepadInput->SetDpadDown(false);
		} else if (e.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_LEFT) {
			gamepadInput->SetDpadLeft(false);
		}
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
