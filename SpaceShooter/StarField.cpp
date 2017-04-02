#include "StarField.h"

StarField::StarField(int starCount) {
	for (int i = 0; i < starCount; i++) {
		int x = rand() % (SCREEN_WIDTH * 2) - (SCREEN_HEIGHT / 2);
		int y = rand() % (SCREEN_HEIGHT * 2) - (SCREEN_HEIGHT / 2);
		int size = rand() % 3 + 2;

		Star *star = new Star(x, y, size, 1);
		stars.push_back(star);
	}
}

StarField::~StarField() {
}

void StarField::Render(SDL_Renderer *renderer) {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	for (Star *star : stars) {
		star->Render(renderer);
	}
}

void StarField::Tick(AxisInput *axisInput) {
	for (Star *star : stars) {
		int x = axisInput->GetLeftX();
		int y = axisInput->GetLeftY();

		star->Move(-x * star->GetSpeed(), -y * star->GetSpeed());
	}
}