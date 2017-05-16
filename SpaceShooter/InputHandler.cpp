#include "InputHandler.h"

InputHandler::InputHandler() {
	inputs = new Inputs();
	screen = MAIN_MENU_SCREEN;
}

InputHandler::~InputHandler() {
}

void InputHandler::HandleInput(SDL_Event e, Game *game) {
	if (e.type == SDL_CONTROLLERAXISMOTION) {
		HandleGamepadAxisInput(e);
	} else if (e.type == SDL_CONTROLLERBUTTONDOWN || e.type == SDL_CONTROLLERBUTTONUP) {
		HandleGamepadButtonInput(e);
	} else if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) {
		HandleKeyboardInput(e);
	}
}

Inputs* InputHandler::GetInputs() {
	return inputs;
}

int InputHandler::GetScreen() {
	return screen;
}

void InputHandler::SetScreen(int screen) {
	this->screen = screen;
}

void InputHandler::HandleKeyboardInput(SDL_Event e) {
	if (e.type == SDL_KEYDOWN) {
		if (e.key.keysym.sym == SDLK_q) {
			inputs->GetKeyboardInput()->SetButtonQ(true);
		} else if (e.key.keysym.sym == SDLK_w) {
			inputs->GetKeyboardInput()->SetButtonW(true);
		} else if (e.key.keysym.sym == SDLK_e) {
			inputs->GetKeyboardInput()->SetButtonE(true);
		} else if (e.key.keysym.sym == SDLK_r) {
			inputs->GetKeyboardInput()->SetButtonR(true);
		} else if (e.key.keysym.sym == SDLK_t) {
			inputs->GetKeyboardInput()->SetButtonT(true);
		} else if (e.key.keysym.sym == SDLK_y) {
			inputs->GetKeyboardInput()->SetButtonY(true);
		} else if (e.key.keysym.sym == SDLK_u) {
			inputs->GetKeyboardInput()->SetButtonU(true);
		} else if (e.key.keysym.sym == SDLK_i) {
			inputs->GetKeyboardInput()->SetButtonI(true);
		} else if (e.key.keysym.sym == SDLK_o) {
			inputs->GetKeyboardInput()->SetButtonO(true);
		} else if (e.key.keysym.sym == SDLK_p) {
			inputs->GetKeyboardInput()->SetButtonP(true);
		} else if (e.key.keysym.sym == SDLK_a) {
			inputs->GetKeyboardInput()->SetButtonA(true);
		} else if (e.key.keysym.sym == SDLK_s) {
			inputs->GetKeyboardInput()->SetButtonS(true);
		} else if (e.key.keysym.sym == SDLK_d) {
			inputs->GetKeyboardInput()->SetButtonD(true);
		} else if (e.key.keysym.sym == SDLK_d) {
			inputs->GetKeyboardInput()->SetButtonD(true);
		} else if (e.key.keysym.sym == SDLK_f) {
			inputs->GetKeyboardInput()->SetButtonF(true);
		} else if (e.key.keysym.sym == SDLK_g) {
			inputs->GetKeyboardInput()->SetButtonG(true);
		} else if (e.key.keysym.sym == SDLK_h) {
			inputs->GetKeyboardInput()->SetButtonH(true);
		} else if (e.key.keysym.sym == SDLK_j) {
			inputs->GetKeyboardInput()->SetButtonJ(true);
		} else if (e.key.keysym.sym == SDLK_k) {
			inputs->GetKeyboardInput()->SetButtonK(true);
		} else if (e.key.keysym.sym == SDLK_l) {
			inputs->GetKeyboardInput()->SetButtonL(true);
		} else if (e.key.keysym.sym == SDLK_z) {
			inputs->GetKeyboardInput()->SetButtonZ(true);
		} else if (e.key.keysym.sym == SDLK_x) {
			inputs->GetKeyboardInput()->SetButtonX(true);
		} else if (e.key.keysym.sym == SDLK_c) {
			inputs->GetKeyboardInput()->SetButtonC(true);
		} else if (e.key.keysym.sym == SDLK_v) {
			inputs->GetKeyboardInput()->SetButtonV(true);
		} else if (e.key.keysym.sym == SDLK_b) {
			inputs->GetKeyboardInput()->SetButtonB(true);
		} else if (e.key.keysym.sym == SDLK_n) {
			inputs->GetKeyboardInput()->SetButtonN(true);
		} else if (e.key.keysym.sym == SDLK_m) {
			inputs->GetKeyboardInput()->SetButtonM(true);
		} else if (e.key.keysym.sym == SDLK_UP) {
			inputs->GetKeyboardInput()->SetArrowUp(true);
		} else if (e.key.keysym.sym == SDLK_RIGHT) {
			inputs->GetKeyboardInput()->SetArrowRight(true);
		} else if (e.key.keysym.sym == SDLK_DOWN) {
			inputs->GetKeyboardInput()->SetArrowDown(true);
		} else if (e.key.keysym.sym == SDLK_LEFT) {
			inputs->GetKeyboardInput()->SetArrowLeft(true);
		} else if (e.key.keysym.sym == SDLK_RETURN) {
			inputs->GetKeyboardInput()->SetButtonEnter(true);
		} else if (e.key.keysym.sym == SDLK_ESCAPE) {
			inputs->GetKeyboardInput()->SetButtonEsc(true);
		} else if (e.key.keysym.sym == SDLK_BACKSPACE) {
			inputs->GetKeyboardInput()->SetButtonBackspace(true);
		}
	} else {
		if (e.key.keysym.sym == SDLK_q) {
			inputs->GetKeyboardInput()->SetButtonQ(false);
		} else if (e.key.keysym.sym == SDLK_w) {
			inputs->GetKeyboardInput()->SetButtonW(false);
		} else if (e.key.keysym.sym == SDLK_e) {
			inputs->GetKeyboardInput()->SetButtonE(false);
		} else if (e.key.keysym.sym == SDLK_r) {
			inputs->GetKeyboardInput()->SetButtonR(false);
		} else if (e.key.keysym.sym == SDLK_t) {
			inputs->GetKeyboardInput()->SetButtonT(false);
		} else if (e.key.keysym.sym == SDLK_y) {
			inputs->GetKeyboardInput()->SetButtonY(false);
		} else if (e.key.keysym.sym == SDLK_u) {
			inputs->GetKeyboardInput()->SetButtonU(false);
		} else if (e.key.keysym.sym == SDLK_i) {
			inputs->GetKeyboardInput()->SetButtonI(false);
		} else if (e.key.keysym.sym == SDLK_o) {
			inputs->GetKeyboardInput()->SetButtonO(false);
		} else if (e.key.keysym.sym == SDLK_p) {
			inputs->GetKeyboardInput()->SetButtonP(false);
		} else if (e.key.keysym.sym == SDLK_a) {
			inputs->GetKeyboardInput()->SetButtonA(false);
		} else if (e.key.keysym.sym == SDLK_s) {
			inputs->GetKeyboardInput()->SetButtonS(false);
		} else if (e.key.keysym.sym == SDLK_d) {
			inputs->GetKeyboardInput()->SetButtonD(false);
		} else if (e.key.keysym.sym == SDLK_d) {
			inputs->GetKeyboardInput()->SetButtonD(false);
		} else if (e.key.keysym.sym == SDLK_f) {
			inputs->GetKeyboardInput()->SetButtonF(false);
		} else if (e.key.keysym.sym == SDLK_g) {
			inputs->GetKeyboardInput()->SetButtonG(false);
		} else if (e.key.keysym.sym == SDLK_h) {
			inputs->GetKeyboardInput()->SetButtonH(false);
		} else if (e.key.keysym.sym == SDLK_j) {
			inputs->GetKeyboardInput()->SetButtonJ(false);
		} else if (e.key.keysym.sym == SDLK_k) {
			inputs->GetKeyboardInput()->SetButtonK(false);
		} else if (e.key.keysym.sym == SDLK_l) {
			inputs->GetKeyboardInput()->SetButtonL(false);
		} else if (e.key.keysym.sym == SDLK_z) {
			inputs->GetKeyboardInput()->SetButtonZ(false);
		} else if (e.key.keysym.sym == SDLK_x) {
			inputs->GetKeyboardInput()->SetButtonX(false);
		} else if (e.key.keysym.sym == SDLK_c) {
			inputs->GetKeyboardInput()->SetButtonC(false);
		} else if (e.key.keysym.sym == SDLK_v) {
			inputs->GetKeyboardInput()->SetButtonV(false);
		} else if (e.key.keysym.sym == SDLK_b) {
			inputs->GetKeyboardInput()->SetButtonB(false);
		} else if (e.key.keysym.sym == SDLK_n) {
			inputs->GetKeyboardInput()->SetButtonN(false);
		} else if (e.key.keysym.sym == SDLK_m) {
			inputs->GetKeyboardInput()->SetButtonM(false);
		} else if (e.key.keysym.sym == SDLK_UP) {
			inputs->GetKeyboardInput()->SetArrowUp(false);
		} else if (e.key.keysym.sym == SDLK_RIGHT) {
			inputs->GetKeyboardInput()->SetArrowRight(false);
		} else if (e.key.keysym.sym == SDLK_DOWN) {
			inputs->GetKeyboardInput()->SetArrowDown(false);
		} else if (e.key.keysym.sym == SDLK_LEFT) {
			inputs->GetKeyboardInput()->SetArrowLeft(false);
		} else if (e.key.keysym.sym == SDLK_RETURN) {
			inputs->GetKeyboardInput()->SetButtonEnter(false);
		} else if (e.key.keysym.sym == SDLK_ESCAPE) {
			inputs->GetKeyboardInput()->SetButtonEsc(false);
		} else if (e.key.keysym.sym == SDLK_BACKSPACE) {
			inputs->GetKeyboardInput()->SetButtonBackspace(false);
		}
	}
}

void InputHandler::HandleGamepadAxisInput(SDL_Event e) {
	int value = e.caxis.value;
	MovementSpeed speed = MapAxisValueToMovementSpeed(value);
	int dir = value >= 0 ? 1 : -1;

	if (screen == MAIN_MENU_SCREEN) {
		if (e.caxis.axis == SDL_CONTROLLER_AXIS_LEFTY && (value >= 8000 || value <= -8000)) {
			inputs->GetGamepadInput()->SetLeftY(dir);
		} else {
			inputs->GetGamepadInput()->SetLeftY(0);
		}
	} else if (screen == GAME_SCREEN) {
		if (e.caxis.axis == SDL_CONTROLLER_AXIS_LEFTX) {
			inputs->GetGamepadInput()->SetLeftX(speed * dir);
		} else if (e.caxis.axis == SDL_CONTROLLER_AXIS_LEFTY) {
			inputs->GetGamepadInput()->SetLeftY(speed * dir);
		} else if (e.caxis.axis == SDL_CONTROLLER_AXIS_RIGHTX) {
			int rightX = value >= 3600 || value <= -3600 ? 1 * dir : 0;
			inputs->GetGamepadInput()->SetRightX(rightX);
		} else if (e.caxis.axis == SDL_CONTROLLER_AXIS_RIGHTY) {
			int rightY = value >= 15000 || value <= -15000 ? 1 * dir : 0;
			inputs->GetGamepadInput()->SetRightY(rightY);
		}
	}
}

void InputHandler::HandleGamepadButtonInput(SDL_Event e) {
	if (e.type == SDL_CONTROLLERBUTTONDOWN) {
		if (e.cbutton.button == SDL_CONTROLLER_BUTTON_A) {
			inputs->GetGamepadInput()->SetButtonA(true);
		} else if (e.cbutton.button == SDL_CONTROLLER_BUTTON_B) {
			inputs->GetGamepadInput()->SetButtonB(true);
		} else if (e.cbutton.button == SDL_CONTROLLER_BUTTON_X) {
			inputs->GetGamepadInput()->SetButtonX(true);
		} else if (e.cbutton.button == SDL_CONTROLLER_BUTTON_Y) {
			inputs->GetGamepadInput()->SetButtonY(true);
		} else if (e.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_UP) {
			inputs->GetGamepadInput()->SetDpadUp(true);
		} else if (e.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_RIGHT) {
			inputs->GetGamepadInput()->SetDpadRight(true);
		} else if (e.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_DOWN) {
			inputs->GetGamepadInput()->SetDpadDown(true);
		} else if (e.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_LEFT) {
			inputs->GetGamepadInput()->SetDpadLeft(true);
		} else if (e.cbutton.button == SDL_CONTROLLER_BUTTON_START) {
			inputs->GetGamepadInput()->TogglePause();
		}
	} else {
		if (e.cbutton.button == SDL_CONTROLLER_BUTTON_A) {
			inputs->GetGamepadInput()->SetButtonA(false);
		} else if (e.cbutton.button == SDL_CONTROLLER_BUTTON_B) {
			inputs->GetGamepadInput()->SetButtonB(false);
		} else if (e.cbutton.button == SDL_CONTROLLER_BUTTON_X) {
			inputs->GetGamepadInput()->SetButtonX(false);
		} else if (e.cbutton.button == SDL_CONTROLLER_BUTTON_Y) {
			inputs->GetGamepadInput()->SetButtonY(false);
		} else if (e.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_UP) {
			inputs->GetGamepadInput()->SetDpadUp(false);
		} else if (e.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_RIGHT) {
			inputs->GetGamepadInput()->SetDpadRight(false);
		} else if (e.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_DOWN) {
			inputs->GetGamepadInput()->SetDpadDown(false);
		} else if (e.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_LEFT) {
			inputs->GetGamepadInput()->SetDpadLeft(false);
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
