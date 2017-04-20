#include "Game.h"

Game::Game(SDL_Renderer *renderer) : Screen() {
	this->renderer = renderer;
	
	paused = false;
	starField = new StarField(200);
	Player *player = new Player(32, 32, renderer, new Vector2(0, 0));
	players.push_back(player);
	Enemy *enemy = new Enemy(32, 32, renderer, new Vector2(0, 0));
	enemies.push_back(enemy);
	Asteroid *asteroid = new Asteroid(32, 32, renderer, new Vector2(32, 0));
	asteroids.push_back(asteroid);
	nextAsteroidSpawnTime = asteroid->GetNextSpawnTime();
	passedAsteroidSpawnTime = zeroNanoseconds;
	timePaused = zeroNanoseconds;

	font = TTF_OpenFont("res/roboto.ttf", 24);
	pauseRect = { SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 - 40, 300, 80 };
	youDiedRect = { SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 - 40, 300, 80 };
	pauseTexture = LoadTextTexture("PAUSED", { 255, 255, 255 }, renderer);
	youDiedTexture = LoadTextTexture("YOU DIED!", { 255, 255, 255 }, renderer);

	currentTickTime = Clock::now();
}

Game::~Game() {
}

SDL_Texture* Game::LoadTextTexture(std::string text, SDL_Color textColor, SDL_Renderer *renderer) {
	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), textColor);
	SDL_Texture *texture = NULL;
	if (surface == NULL) {
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else {
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		if (texture == NULL) {
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}

		SDL_FreeSurface(surface);
	}

	return texture;
}

void Game::SetPaused(bool paused) {
	this->paused = paused;
}

bool Game::GetPaused() {
	return paused;
}

StarField* Game::GetStarField() {
	return starField;
}

void Game::Tick(GamepadInput *gamepadInput, KeyboardInput *keyboardInput) {
	SetPaused(gamepadInput->GetStartButton());

	previousTickTime = currentTickTime;
	currentTickTime = Clock::now();
	auto deltaTime = currentTickTime - previousTickTime;

	if (!paused) {
		passedAsteroidSpawnTime += std::chrono::duration_cast<Nanoseconds>(deltaTime);
		if (passedAsteroidSpawnTime >= nextAsteroidSpawnTime) {
			Asteroid *asteroid = new Asteroid(32, 32, renderer, new Vector2(32, 0));
			asteroids.push_back(asteroid);
			passedAsteroidSpawnTime -= nextAsteroidSpawnTime;
			this->nextAsteroidSpawnTime = asteroid->GetNextSpawnTime();
		}

		if (players.size() > 0) {
			starField->Tick(gamepadInput);
		}
		for (Player *player : players) {
			player->Tick(gamepadInput);
		}
		for (Enemy *enemy : enemies) {
			enemy->Tick(gamepadInput);
		}
		for (Asteroid *asteroid : asteroids) {
			asteroid->Tick(gamepadInput);
		}

		for (Enemy *enemy : enemies) {
			for (Player *player : players) {
				if (CheckCollision(player->GetRect(), enemy->GetRect())) {
					player->TakeDamage(enemy->GetDamage());
				}
			}
		}

		for (Player *player : players) {
			for (Bullet *bullet : player->GetBullets()) {
				for (Enemy *enemy : enemies) {
					if (CheckCollision(bullet->GetRect(), enemy->GetRect())) {
						enemy->TakeDamage(bullet->GetDamage());
						bullet->SetCollision(true);
					}
				}
				for (Asteroid *asteroid : asteroids) {
					if (CheckCollision(bullet->GetRect(), asteroid->GetRect())) {
						asteroid->TakeDamage(bullet->GetDamage());
						bullet->SetCollision(true);
					}
				}
			}
		}

		for (Asteroid *asteroid : asteroids) {
			for (Player *player : players) {
				if (CheckCollision(asteroid->GetRect(), player->GetRect())) {
					asteroid->TakeDamage(asteroid->GetHealth());
					player->TakeDamage(asteroid->GetDamage());
				}
			}
		}

		enemies.erase(
			std::remove_if(
				enemies.begin(), enemies.end(),
				[&](Enemy *enemy) {
			bool destroyable = enemy->IsDestroyable();
			if (destroyable) delete enemy;
			return destroyable;
		}
			),
			enemies.end()
			);

		asteroids.erase(
			std::remove_if(
				asteroids.begin(), asteroids.end(),
				[&](Asteroid *asteroid) {
			bool destroyable = asteroid->IsDestroyable();
			if (destroyable) delete asteroid;
			return destroyable;
		}
			),
			asteroids.end()
			);

		players.erase(
			std::remove_if(
				players.begin(), players.end(),
				[&](Player *player) {
					bool destroyable = player->IsDestroyable();
					if (destroyable) delete player;
					return destroyable;
				}
			),
			players.end()
		);
	}
}

void Game::Render() {
	starField->Render(renderer);
	for (Asteroid *asteroid : asteroids) {
		asteroid->Render(renderer);
	}
	for (Enemy *enemy : enemies) {
		enemy->Render(renderer);
	}
	for (Player *player : players) {
		player->Render(renderer);
	}	
	if (players.empty()) {
		SDL_RenderCopy(renderer, youDiedTexture, NULL, &youDiedRect);
	}
	if (paused) {
		SDL_RenderCopy(renderer, pauseTexture, NULL, &pauseRect);
	}
}

bool Game::CheckCollision(SDL_Rect a, SDL_Rect b) {
	int leftA = a.x;
	int rightA = a.x + a.w;
	int topA = a.y;
	int bottomA = a.y + a.h;

	int leftB = b.x;
	int rightB = b.x + b.w;
	int topB = b.y;
	int bottomB = b.y + b.h;

	return bottomA > topB && topA < bottomB && rightA > leftB && leftA < rightB;
}

std::vector<Asteroid*> Game::GetAsteroids() {
	return asteroids;
}

std::vector<Enemy*> Game::GetEnemies() {
	return enemies;
}
