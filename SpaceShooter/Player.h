#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>

class Player {
public:
	Player(int, int);
	SDL_Rect GetRect();
	void Move(int x, int y);
	void Tick();
private:
	SDL_Rect rect;
};

#endif