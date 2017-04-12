#include "Screen.h"

Screen::Screen() {
	running = true;
	nextScreen = -1;
}

Screen::~Screen() {
}

void Screen::Tick(GamepadInput *gamepadInput, KeyboardInput *keyboardInput) {
}

void Screen::Render() {
}

bool Screen::IsRunning() {
	return running;
}

int Screen::GetNextScreen() {
	return nextScreen;
}

void Screen::SetRunning(bool running) {
	this->running = running;
}

void Screen::SetNextScreen(int nextScreen) {
	this->nextScreen = nextScreen;
}
