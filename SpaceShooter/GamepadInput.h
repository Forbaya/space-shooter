#ifndef GAMEPAD_H
#define GAMEPAD_H

#include "Constants.h"

class GamepadInput {
	public:
		GamepadInput();
		~GamepadInput();
		int GetLeftX();
		int GetLeftY();
		int GetRightX();
		int GetRightY();
		bool GetButtonA();
		bool GetButtonB();
		bool GetButtonX();
		bool GetButtonY();
		void SetLeftX(int leftX);
		void SetLeftY(int leftY);
		void SetRightX(int rightX);
		void SetRightY(int rightY);
		void SetButtonA(bool buttonA);
		void SetButtonB(bool buttonB);
		void SetButtonX(bool buttonX);
		void SetButtonY(bool buttonY);
	private:
		int leftX;
		int leftY;
		int rightX;
		int rightY;
		bool buttonA;
		bool buttonB;
		bool buttonX;
		bool buttonY;
};

#endif