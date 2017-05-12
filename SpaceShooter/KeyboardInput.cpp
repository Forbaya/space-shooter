#include "KeyboardInput.h"

KeyboardInput::KeyboardInput() {
	arrowUp = false;
	arrowRight = false;
	arrowDown = false;
	arrowLeft = false;
	buttonW = false;
	buttonA = false;
	buttonS = false;
	buttonD = false;
	buttonEnter = false;
	buttonEsc = false;
}

KeyboardInput::~KeyboardInput() {
}

bool KeyboardInput::GetArrowUp() {
	return arrowUp;
}

bool KeyboardInput::GetArrowRight() {
	return arrowRight;
}

bool KeyboardInput::GetArrowDown() {
	return arrowDown;
}

bool KeyboardInput::GetArrowLeft() {
	return arrowLeft;
}

bool KeyboardInput::GetButtonW() {
	return buttonW;
}

bool KeyboardInput::GetButtonA() {
	return buttonA;
}

bool KeyboardInput::GetButtonS() {
	return buttonS;
}

bool KeyboardInput::GetButtonD() {
	return buttonD;
}

bool KeyboardInput::GetButtonEnter() {
	return buttonEnter;
}

bool KeyboardInput::GetButtonEsc() {
	return buttonEsc;
}

void KeyboardInput::SetArrowUp(bool arrowUp) {
	this->arrowUp = arrowUp;
}

void KeyboardInput::SetArrowRight(bool arrowRight) {
	this->arrowRight = arrowRight;
}

void KeyboardInput::SetArrowDown(bool arrowDown) {
	this->arrowDown = arrowDown;
}

void KeyboardInput::SetArrowLeft(bool arrowLeft) {
	this->arrowLeft = arrowLeft;
}

void KeyboardInput::SetButtonW(bool buttonW) {
	this->buttonW = buttonW;
}

void KeyboardInput::SetButtonA(bool buttonA) {
	this->buttonA = buttonA;
}

void KeyboardInput::SetButtonS(bool buttonS) {
	this->buttonS = buttonS;
}

void KeyboardInput::SetButtonD(bool buttonD) {
	this->buttonD = buttonD;
}

void KeyboardInput::SetButtonEnter(bool buttonEnter) {
	this->buttonEnter = buttonEnter;
}

void KeyboardInput::SetButtonEsc(bool buttonEsc) {
	this->buttonEsc = buttonEsc;
}
