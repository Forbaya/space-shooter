#ifndef INPUTS_H
#define INPUTS_H

#include "GamepadInput.h"
#include "KeyboardInput.h"

class Inputs {
	public:
		Inputs();
		~Inputs();
		GamepadInput* GetGamepadInput();
		KeyboardInput* GetKeyboardInput();
	private:
		GamepadInput *gamepadInput;
		KeyboardInput *keyboardInput;
};

#endif