#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include "Player.h"
#include "StarField.h"

class Game {
	public:
		Game();
		bool IsRunning();
		void Start();
		void Stop();
		Player *GetPlayer();
		void Tick();
		void Render(SDL_Surface *screen);
	private:
		bool running;
		Player *player;
		StarField *starField;

};

#endif