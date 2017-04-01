#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include "AxisInput.h"
#include "Player.h"
#include "StarField.h"

class Game {
	public:
		Game(SDL_Renderer *renderer);
		~Game();
		bool IsRunning();
		void Start();
		void Stop();
		Player* GetPlayer();
		StarField* GetStarField();
		void Tick(AxisInput *axisInput);
		void Render(SDL_Surface *screen);
	private:
		bool running;
		Player *player;
		StarField *starField;
		SDL_Renderer *renderer;
};

#endif