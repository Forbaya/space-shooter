#ifndef GAME_H
#define GAME_H

#include <SDL_ttf.h>
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
		SDL_Texture* LoadTextTexture(std::string text, SDL_Color textColor, SDL_Renderer *renderer);
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
		Nanoseconds timePaused;
		SDL_Rect pauseRect;
		SDL_Rect youDiedRect;
		SDL_Texture *pauseTexture;
		SDL_Texture *youDiedTexture;
		TTF_Font *font;
};

#endif