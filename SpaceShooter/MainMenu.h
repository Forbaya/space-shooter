#ifndef MAINMENU_H
#define MAINMENU_H

#include <SDL.h>
#include "AxisInput.h"

class MainMenu {
	MainMenu(SDL_Renderer *renderer);
	~MainMenu();
	void Tick(AxisInput *axisInput);
	void Render();
};

#endif