#include "Game.h"
#include <iostream>

Game::Game(SDL_Renderer *renderer) : Screen() {
	this->renderer = renderer;
	
	score = 0;
	pScore = &score;

	paused = false;
	starField = new StarField(200);
	Player *player = new Player(32, 32, renderer, new Vector2(0, 0), pScore);
	players.push_back(player);
	Enemy *enemy = new Enemy(32, 32, renderer, new Vector2(0, 0), pScore);
	enemies.push_back(enemy);
	Asteroid *asteroid = new Asteroid(32, 32, renderer, new Vector2(32, 0), pScore);
	asteroids.push_back(asteroid);
	nextAsteroidSpawnTime = asteroid->GetNextSpawnTime();
	passedAsteroidSpawnTime = zeroNanoseconds;
	timePaused = zeroNanoseconds;
	textCooldown = Nanoseconds(150000000);
	textCooldownLeft = zeroNanoseconds;
	playerName = "";

	font = TTF_OpenFont("res/roboto.ttf", 24);
	pauseRect = { SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 - 40, 300, 80 };
	youDiedRect = { SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 - 40, 300, 80 };
	int scoreDigits = CountDigitsInInteger(score);
	scoreRect = { SCREEN_WIDTH - 60 - scoreDigits * 15, 50, 30 * scoreDigits, 30 };
	scoreTextRect = { SCREEN_WIDTH - 75 - 20, 20, 75, 28 };
	int playerHealth = player->GetHealth();
	healthTextRect = { 20, 20, 90, 28 };
	healthBarRect = { 20, 50, playerHealth * 30, 30 };
	healthLeftRect = { 20, 50, playerHealth * 30, 30 };
	playerNameRect = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 50, 100, 50 };

	pauseTexture = LoadTextTexture("PAUSED", { 255, 255, 255 }, renderer);
	youDiedTexture = LoadTextTexture("YOU DIED!", { 255, 255, 255 }, renderer);
	scoreTexture = LoadTextTexture(std::to_string(score), { 255, 255, 255 }, renderer);
	healthTextTexture = LoadTextTexture("Health", { 255, 255, 255 }, renderer);
	scoreTextTexture = LoadTextTexture("Score", { 255, 255, 255 }, renderer);
	playerNameTexture = LoadTextTexture(playerName, { 255, 255, 255 }, renderer);

	currentTickTime = Clock::now();
}

Game::~Game() {
}

SDL_Texture* Game::LoadTextTexture(std::string text, SDL_Color textColor, SDL_Renderer *renderer) {
	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), textColor);
	SDL_Texture *texture = NULL;
	if (surface == NULL) {
		std::string error = TTF_GetError();
		if (error.compare("Text has zero width") != 0) {
			printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
		}
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

void Game::Tick(Inputs *inputs) {
	previousTickTime = currentTickTime;
	currentTickTime = Clock::now();
	auto deltaTime = currentTickTime - previousTickTime;

	if (!players.empty()) {
		SetPaused(inputs->GetGamepadInput()->GetStartButton());

		if (!paused) {
			passedAsteroidSpawnTime += std::chrono::duration_cast<Nanoseconds>(deltaTime);
			if (passedAsteroidSpawnTime >= nextAsteroidSpawnTime) {
				Asteroid *asteroid = new Asteroid(32, 32, renderer, new Vector2(32, 0), pScore);
				asteroids.push_back(asteroid);
				passedAsteroidSpawnTime -= nextAsteroidSpawnTime;
				this->nextAsteroidSpawnTime = asteroid->GetNextSpawnTime();
			}

			if (players.size() > 0) {
				starField->Tick(inputs);
			}
			for (Player *player : players) {
				player->Tick(inputs);
			}
			for (Enemy *enemy : enemies) {
				enemy->Tick(inputs);
			}
			for (Asteroid *asteroid : asteroids) {
				asteroid->Tick(inputs);
			}

			HandleCollision();

			SDL_DestroyTexture(scoreTexture);
			scoreTexture = LoadTextTexture(std::to_string(score), { 255, 255, 255 }, renderer);

			EraseUnnecessaryObjects();


			if (players.size() == 0) {
				healthLeftRect = { 20, 50, 0, 30 };
			} else {
				healthLeftRect = { 20, 50, players.at(0)->GetHealth() * 30, 30 };
			}
		}
	} else {
		HandlePlayerNameInput(inputs, std::chrono::duration_cast<Nanoseconds>(deltaTime));
	}
}

void Game::HandlePlayerNameInput(Inputs *inputs, Nanoseconds deltaTime) {
	textCooldownLeft += deltaTime;
	
	if (textCooldownLeft >= textCooldown && playerName.length() < 16) {
		HandleButton(inputs, "Q");
		HandleButton(inputs, "W");
		HandleButton(inputs, "E");
		HandleButton(inputs, "R");
		HandleButton(inputs, "T");
		HandleButton(inputs, "Y");
		HandleButton(inputs, "U");
		HandleButton(inputs, "I");
		HandleButton(inputs, "O");
		HandleButton(inputs, "P");
		HandleButton(inputs, "A");
		HandleButton(inputs, "S");
		HandleButton(inputs, "D");
		HandleButton(inputs, "F");
		HandleButton(inputs, "G");
		HandleButton(inputs, "H");
		HandleButton(inputs, "J");
		HandleButton(inputs, "K");
		HandleButton(inputs, "L");
		HandleButton(inputs, "Z");
		HandleButton(inputs, "X");
		HandleButton(inputs, "C");
		HandleButton(inputs, "V");
		HandleButton(inputs, "B");
		HandleButton(inputs, "N");
		HandleButton(inputs, "M");
	}
	if (inputs->GetKeyboardInput()->GetButtonBackspace() && textCooldownLeft >= textCooldown && playerName.length() >= 1) {
		playerName = playerName.substr(0, playerName.length() - 1);
		textCooldownLeft = zeroNanoseconds;
		SDL_DestroyTexture(playerNameTexture);
		ChangePlayerNameRectLength((int)playerName.length() * 15);
		playerNameTexture = LoadTextTexture(playerName, { 255, 255, 255 }, renderer);
	}
	if (playerName.length() > 0 && (inputs->GetGamepadInput()->GetButtonA() || inputs->GetKeyboardInput()->GetButtonEnter())) {
		SetNextScreen(MAIN_MENU_SCREEN);
	}
}

void Game::HandleButton(Inputs *inputs, std::string button) {
	if (inputs->GetKeyboardInput()->GetButton(button)) {
		playerName += button;
		textCooldownLeft = zeroNanoseconds;
		SDL_DestroyTexture(playerNameTexture);
		ChangePlayerNameRectLength((int)playerName.length() * 15);
		playerNameTexture = LoadTextTexture(playerName, { 255, 255, 255 }, renderer);
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
		if (playerName.length() > 0) {
			SDL_RenderCopy(renderer, playerNameTexture, NULL, &playerNameRect);
		}
	}
	if (paused) {
		SDL_RenderCopy(renderer, pauseTexture, NULL, &pauseRect);
	}

	SDL_SetRenderDrawColor(renderer, 50, 50, 50, 50);
	SDL_RenderFillRect(renderer, &healthBarRect);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
	SDL_RenderFillRect(renderer, &healthLeftRect);

	int scoreDigits = CountDigitsInInteger(score);
	scoreRect = { SCREEN_WIDTH - 60 - scoreDigits * 15, 50, 30 * scoreDigits, 30 };
	SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);
	SDL_RenderCopy(renderer, healthTextTexture, NULL, &healthTextRect);
	SDL_RenderCopy(renderer, scoreTextTexture, NULL, &scoreTextRect);
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

long Game::GetScore() {
	return score;
}

long* Game::GetScorePointer() {
	return pScore;
}

int Game::CountDigitsInInteger(int x) {
	int digits = 0;

	do {
		digits++;
		x /= 10;
	} while (x);

	return digits;
}

void Game::EraseUnnecessaryObjects() {
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

void Game::HandleCollision() {
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
}

void Game::ChangePlayerNameRectLength(int length) {
	playerNameRect = { SCREEN_WIDTH / 2 - length / 2, SCREEN_HEIGHT / 2 + 50, length, 50 };
}
