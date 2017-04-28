#include "Inputs.h"

Inputs::Inputs() {
	this->gamepadInput = new GamepadInput();
	this->keyboardInput = new KeyboardInput();
}

Inputs::~Inputs() {
	delete gamepadInput;
	delete keyboardInput;
}

GamepadInput* Inputs::GetGamepadInput() {
	return this->gamepadInput;
}

KeyboardInput* Inputs::GetKeyboardInput() {
	return this->keyboardInput;
}
