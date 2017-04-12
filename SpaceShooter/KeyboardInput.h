#ifndef KEYBOARDINPUT_H
#define KEYBOARDINPUT_H

#include "InputMap.h"

class KeyboardInput : public InputMap {
	public:
		KeyboardInput();
		~KeyboardInput();
		bool GetArrowUp();
		bool GetArrowRight();
		bool GetArrowDown();
		bool GetArrowLeft();
		bool GetButtonW();
		bool GetButtonA();
		bool GetButtonS();
		bool GetButtonD();
		bool GetButtonEnter();
		void SetArrowUp(bool arrowUp);
		void SetArrowRight(bool arrowRight);
		void SetArrowDown(bool arrowDown);
		void SetArrowLeft(bool arrowLeft);
		void SetButtonW(bool buttonW);
		void SetButtonA(bool buttonA);
		void SetButtonS(bool buttonS);
		void SetButtonD(bool buttonD);
		void SetButtonEnter(bool buttonEnter);
	private:
		bool arrowUp;
		bool arrowRight;
		bool arrowDown;
		bool arrowLeft;
		bool buttonW;
		bool buttonA;
		bool buttonS;
		bool buttonD;
		bool buttonEnter;
};

#endif