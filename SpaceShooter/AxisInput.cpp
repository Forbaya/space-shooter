#include "AxisInput.h"

AxisInput::AxisInput() {
	leftX = NO_SPEED;
	leftY = NO_SPEED;
	rightX = NO_SPEED;
	rightY = NO_SPEED;
}

AxisInput::~AxisInput() {
}

int AxisInput::GetLeftX() {
	return leftX;
}

int AxisInput::GetLeftY() {
	return leftY;
}

int AxisInput::GetRightX() {
	return rightX;
}

int AxisInput::GetRightY() {
	return rightY;
}

void AxisInput::SetLeftX(int newLeftX) {
	leftX = newLeftX;
}

void AxisInput::SetLeftY(int newLeftY) {
	leftY = newLeftY;
}

void AxisInput::SetRightX(int newRightX) {
	rightX = newRightX;
}

void AxisInput::SetRightY(int newRightY) {
	rightY = newRightY;
}
