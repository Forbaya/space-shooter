#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include "Asteroid.h"
#include "Enemy.h"
#include "GamepadInput.h"
#include "KeyboardInput.h"
#include "Player.h"
#include "Screen.h"
#include "StarField.h"

class Game : public Screen {
	public:
		Game(SDL_Renderer *renderer);
		~Game();
		void SetPaused(bool paused);
		bool GetPaused();
		StarField* GetStarField();
		void Tick(GamepadInput *gamepadInput, KeyboardInput *keyboardInput);
		void Render();
		bool CheckCollision(SDL_Rect a, SDL_Rect b);
		std::vector<Asteroid*> GetAsteroids();
		std::vector<Enemy*> GetEnemies();
	private:
		bool paused;
		StarField *starField;
		SDL_Renderer *renderer;
		std::vector<Asteroid*> asteroids;
		std::vector<Enemy*> enemies;
		std::vector<Player*> players;
		Time currentTickTime;
		Time previousTickTime;
		Nanoseconds nextAsteroidSpawnTime;
		Nanoseconds passedAsteroidSpawnTime;
};

#endif