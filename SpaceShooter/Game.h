#ifndef GAME_H
#define GAME_H

#include <SDL_ttf.h>
#include <SDL.h>
#include "Asteroid.h"
#include "Database.h"
#include "Enemy.h"
#include "GamepadInput.h"
#include "KeyboardInput.h"
#include "Player.h"
#include "Screen.h"
#include "StarField.h"

class Game : public Screen {
	public:
		Game(SDL_Renderer *renderer, Database *database);
		virtual ~Game();
		void SetPaused(bool paused);
		bool GetPaused();
		StarField* GetStarField();
		void Tick(Inputs *inputs);
		void HandlePlayerNameInput(Inputs *inputs, Nanoseconds deltaTime);
		void HandleButton(Inputs *inputs, std::string);
		void Render();
		bool CheckCollision(SDL_Rect a, SDL_Rect b);
		std::vector<Asteroid*> GetAsteroids();
		std::vector<Enemy*> GetEnemies();
		long GetScore();
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
		Nanoseconds textCooldown;
		Nanoseconds textCooldownLeft;
		Nanoseconds underscoreBlinkTime;
		Nanoseconds underscoreBlinkInterval;
		SDL_Rect pauseRect;
		SDL_Rect youDiedRect;
		SDL_Rect scoreRect;
		SDL_Rect healthTextRect;
		SDL_Rect healthBarRect;
		SDL_Rect healthLeftRect;
		SDL_Rect scoreTextRect;
		SDL_Rect playerNameRect;
		SDL_Rect playerNameInstructionsRect;
		SDL_Rect blinkingUnderscoreRect;
		SDL_Texture *pauseTexture;
		SDL_Texture *youDiedTexture;
		SDL_Texture *scoreTexture;
		SDL_Texture *healthTextTexture;
		SDL_Texture *scoreTextTexture;
		SDL_Texture *playerNameTexture;
		SDL_Texture *playerNameInstructionsTexture;
		SDL_Texture *blinkingUnderscoreTexture;
		long score;
		int CountDigitsInInteger(int x);
		void EraseUnnecessaryObjects();
		void HandleCollision();
		std::string playerName;
		void ChangePlayerNameRectLength(int length);
		void HandleBlinkingUnderscore(Nanoseconds deltaTime);
		Database *database;
		bool showUnderscore;
};

#endif