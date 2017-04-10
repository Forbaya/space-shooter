#include "GamepadInput.h"

GamepadInput::GamepadInput() {
	leftX = NO_SPEED;
	leftY = NO_SPEED;
	rightX = NO_SPEED;
	rightY = NO_SPEED;

	buttonA = false;
	buttonB = false;
	buttonX = false;
	buttonY = false;
}

GamepadInput::~GamepadInput() {
}

int GamepadInput::GetLeftX() {
	return leftX;
}

int GamepadInput::GetLeftY() {
	return leftY;
}

int GamepadInput::GetRightX() {
	return rightX;
}

int GamepadInput::GetRightY() {
	return rightY;
}

bool GamepadInput::GetButtonA() {
	return buttonA;
}

bool GamepadInput::GetButtonB() {
	return buttonB;
}

bool GamepadInput::GetButtonX() {
	return buttonX;
}

bool GamepadInput::GetButtonY() {
	return buttonY;
}

bool GamepadInput::GetDpadUp() {
	return dpadUp;
}

bool GamepadInput::GetDpadRight() {
	return dpadRight;
}

bool GamepadInput::GetDpadDown() {
	return dpadDown;
}

bool GamepadInput::GetDpadLeft() {
	return dpadLeft;
}

void GamepadInput::SetLeftX(int leftX) {
	this->leftX = leftX;
}

void GamepadInput::SetLeftY(int leftY) {
	this->leftY = leftY;
}

void GamepadInput::SetRightX(int rightX) {
	this->rightX = rightX;
}

void GamepadInput::SetRightY(int rightY) {
	this->rightY = rightY;
}

void GamepadInput::SetButtonA(bool buttonA) {
	this->buttonA = buttonA;
}

void GamepadInput::SetButtonB(bool buttonB) {
	this->buttonB = buttonB;
}

void GamepadInput::SetButtonX(bool buttonX) {
	this->buttonX = buttonX;
}

void GamepadInput::SetButtonY(bool buttonY) {
	this->buttonY = buttonY;
}

void GamepadInput::SetDpadUp(bool dpadUp) {
	this->dpadUp = dpadUp;
}

void GamepadInput::SetDpadRight(bool dpadRight) {
	this->dpadRight = dpadRight;
}

void GamepadInput::SetDpadDown(bool dpadDown) {
	this->dpadDown = dpadDown;
}

void GamepadInput::SetDpadLeft(bool dpadLeft) {
	this->dpadLeft = dpadLeft;
}
