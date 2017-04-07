#ifndef MAINMENU_H
#define MAINMENU_H

#include <SDL.h>
#include "AxisInput.h"

class MainMenu {
	public:
		MainMenu(SDL_Renderer *renderer);
		~MainMenu();
		void Tick(AxisInput *axisInput);
		void Render();
	private:
		SDL_Renderer *renderer;
};

#endif