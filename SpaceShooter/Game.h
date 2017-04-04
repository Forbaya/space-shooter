#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include "Asteroid.h"
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
		std::vector<Asteroid*> GetAsteroids();
		std::vector<Enemy*> GetEnemies();
	private:
		bool running;
		Player *player;
		StarField *starField;
		SDL_Renderer *renderer;
		std::vector<Asteroid*> asteroids;
		std::vector<Enemy*> enemies;
		Time currentTickTime;
		Time previousTickTime;
		Nanoseconds nextAsteroidSpawnTime;
		Nanoseconds passedAsteroidSpawnTime;
};

#endif