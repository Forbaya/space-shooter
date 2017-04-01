#include <SDL_image.h>
#include <SDL.h>
#include <vector>
#include "AxisInput.h"
#include "Constants.h"
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
		SDL_RenderDrawRect(renderer, &star->GetRect());
	}
}

void StarField::Tick(AxisInput *axisInput) {
	for (Star *star : stars) {
		int x = axisInput->GetLeftX();
		int y = axisInput->GetLeftY();

		star->Move(-x * star->GetSpeed(), -y * star->GetSpeed());
	}
}