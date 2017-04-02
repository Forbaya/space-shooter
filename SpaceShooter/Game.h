#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include "AxisInput.h"
#include "Enemy.h"
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
		void Render();
		bool CheckCollision(SDL_Rect a, SDL_Rect b);
	private:
		bool running;
		Player *player;
		Enemy *enemy;
		StarField *starField;
		SDL_Renderer *renderer;
};

#endif