#include <SDL.h>
#include <vector>
#include "Constants.h"
#include "StarField.h"

StarField::StarField(int starCount) {
	for (int i = 0; i < starCount; i++) {
		int x = rand() % (SCREEN_WIDTH + 1);
		int y = rand() % (SCREEN_HEIGHT + 1);
		int size = rand() % 3 + 2;

		Star *star = new Star(x, y, size, 1);
		stars.push_back(*star);
	}
}

void StarField::Render(SDL_Surface *screen) {
	for (Star star : stars) {
		SDL_FillRect(screen, &star.GetRect(), SDL_MapRGB(screen->format, 255, 255, 255));
	}
}
