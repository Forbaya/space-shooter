#ifndef GAME_H
#define GAME_H

#include "Player.h"

class Game {
	public:
		Game();
		bool IsRunning();
		void Start();
		void Stop();
		Player *GetPlayer();
		void Tick();
	private:
		bool running;
		Player *player = new Player(16, 16);
};

#endif