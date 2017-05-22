#include "Game.h"
#include <iostream>

Game::Game(SDL_Renderer *renderer, Database *database) : Screen() {
	this->renderer = renderer;
	this->database = database;

	score = 0;
	paused = false;
	showUnderscore = false;
	starField = new StarField(200);
	Player *player = new Player(32, 32, renderer, new Vector2(0, 0));
	players.push_back(player);
	//Enemy *enemy = new Enemy(32, 32, renderer, new Vector2(0, 0));
	//enemies.push_back(enemy);
	Asteroid *asteroid = new Asteroid(32, 32, renderer, new Vector2(32, 0));
	asteroids.push_back(asteroid);
	nextAsteroidSpawnTime = asteroid->GetNextSpawnTime();
	passedAsteroidSpawnTime = zeroNanoseconds;
	timePaused = zeroNanoseconds;
	textCooldown = Nanoseconds(150000000);
	textCooldownLeft = zeroNanoseconds;
	playerName = "";
	underscoreBlinkTime = zeroNanoseconds;
	underscoreBlinkInterval = Nanoseconds(500000000);

	pauseRect = { SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 - 40, 300, 80 };
	youDiedRect = { SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 - 100, 300, 80 };
	int scoreDigits = CountDigitsInInteger(score);
	scoreRect = { SCREEN_WIDTH - 60 - scoreDigits * 15, 40, 30 * scoreDigits, 30 };
	scoreTextRect = { SCREEN_WIDTH - 75 - 20, 10, 75, 28 };
	int playerHealth = player->GetHealth();
	healthTextRect = { 20, 10, 90, 28 };
	healthBarRect = { 20, 40, playerHealth * 30, 20 };
	healthLeftRect = { 20, 40, playerHealth * 30, 20 };
	playerNameRect = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 50, 100, 50 };
	playerNameInstructionsRect = { SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 - 10, 300, 50 };
	blinkingUnderscoreRect = { SCREEN_WIDTH / 2 - 9, SCREEN_HEIGHT / 2 + 50, 18, 50 };

	pauseTexture = LoadTextTexture("PAUSED", white, renderer);
	youDiedTexture = LoadTextTexture("YOU DIED!", white, renderer);
	scoreTexture = LoadTextTexture(std::to_string(score), white, renderer);
	healthTextTexture = LoadTextTexture("Health", white, renderer);
	scoreTextTexture = LoadTextTexture("Score", white, renderer);
	playerNameTexture = LoadTextTexture(playerName, white, renderer);
	playerNameInstructionsTexture = LoadTextTexture("Enter your name", white, renderer);
	blinkingUnderscoreTexture = LoadTextTexture("_", white, renderer);

	currentTickTime = Clock::now();
}

Game::~Game() {
	delete starField;

	for (auto it = asteroids.begin(); it != asteroids.end(); ++it) {
		delete *it;
	}
	asteroids.clear();

	for (auto it = enemies.begin(); it != enemies.end(); ++it) {
		delete *it;
	}
	enemies.clear();

	for (auto it = players.begin(); it != players.end(); ++it) {
		delete *it;
	}
	players.clear();

	SDL_DestroyTexture(pauseTexture);
	SDL_DestroyTexture(youDiedTexture);
	SDL_DestroyTexture(scoreTexture);
	SDL_DestroyTexture(healthTextTexture);
	SDL_DestroyTexture(scoreTextTexture);
	SDL_DestroyTexture(playerNameTexture);
	SDL_DestroyTexture(playerNameInstructionsTexture);
	SDL_DestroyTexture(blinkingUnderscoreTexture);
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

	if (!paused) {
		passedAsteroidSpawnTime += std::chrono::duration_cast<Nanoseconds>(deltaTime);
		if (passedAsteroidSpawnTime >= nextAsteroidSpawnTime) {
			Asteroid *asteroid = new Asteroid(32, 32, renderer, new Vector2(32, 0));
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
		for (HealthDrop *healthDrop : healthDrops) {
			healthDrop->Tick(inputs);
		}

		HandleCollision();

		SDL_DestroyTexture(scoreTexture);
		scoreTexture = LoadTextTexture(std::to_string(score), white, renderer);

		EraseUnnecessaryObjects();

		if (players.size() == 0) {
			healthLeftRect = { 20, 40, 0, 20 };
		} else {
			healthLeftRect = { 20, 40, players.at(0)->GetHealth() * 30, 20 };
		}
	}

	if (players.empty()) {
		HandlePlayerNameInput(inputs, std::chrono::duration_cast<Nanoseconds>(deltaTime));
		HandleBlinkingUnderscore(deltaTime);
	} else {
		SetPaused(inputs->GetGamepadInput()->GetStartButton());
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
		SDL_DestroyTexture(blinkingUnderscoreTexture);
		int playerNameLengthInPixels = ((int)playerName.length() * 15);
		ChangePlayerNameRectLength(playerNameLengthInPixels);
		int blinkingUnderscoreLeftX = SCREEN_WIDTH / 2 + playerNameLengthInPixels / 2 + 5;
		blinkingUnderscoreRect = { blinkingUnderscoreLeftX, SCREEN_HEIGHT / 2 + 50, 18, 50 };
		playerNameTexture = LoadTextTexture(playerName, white, renderer);
		blinkingUnderscoreTexture = LoadTextTexture("_", white, renderer);
	}
	if (playerName.length() > 0 && (inputs->GetGamepadInput()->GetButtonA() || inputs->GetKeyboardInput()->GetButtonEnter())) {
		SetNextScreen(MAIN_MENU_SCREEN);
		database->InsertHiscore(playerName, score);
	}
}

void Game::HandleButton(Inputs *inputs, std::string button) {
	if (inputs->GetKeyboardInput()->GetButton(button) && playerName.length() < 16) {
		playerName += button;
		textCooldownLeft = zeroNanoseconds;
		SDL_DestroyTexture(playerNameTexture);
		SDL_DestroyTexture(blinkingUnderscoreTexture);
		int playerNameLengthInPixels = ((int)playerName.length() * 15);
		ChangePlayerNameRectLength(playerNameLengthInPixels);
		int blinkingUnderscoreLeftX = SCREEN_WIDTH / 2 + playerNameLengthInPixels / 2 + 5;
		blinkingUnderscoreRect = { blinkingUnderscoreLeftX, SCREEN_HEIGHT / 2 + 50, 18, 50 };
		playerNameTexture = LoadTextTexture(playerName, white, renderer);
		blinkingUnderscoreTexture = LoadTextTexture("_", white, renderer);
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
	for (HealthDrop *healthDrop : healthDrops) {
		healthDrop->Render(renderer);
	}

	if (players.empty()) {
		SDL_RenderCopy(renderer, youDiedTexture, NULL, &youDiedRect);
		SDL_RenderCopy(renderer, playerNameInstructionsTexture, NULL, &playerNameInstructionsRect);
		if (playerName.length() > 0) {
			SDL_RenderCopy(renderer, playerNameTexture, NULL, &playerNameRect);
		}
		if (playerName.length() < 16 && showUnderscore) {
			SDL_RenderCopy(renderer, blinkingUnderscoreTexture, NULL, &blinkingUnderscoreRect);
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
	scoreRect = { SCREEN_WIDTH - 60 - scoreDigits * 15, 40, 30 * scoreDigits, 30 };
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

	healthDrops.erase(
		std::remove_if(
			healthDrops.begin(), healthDrops.end(),
			[&](HealthDrop *healthDrops) {
				bool destroyable = healthDrops->GetCollision();
				if (destroyable) delete healthDrops;
				return destroyable;
			}
		),
		healthDrops.end()
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
					if (enemy->IsDead()) {
						score += enemy->GetReward();
					}
				}
			}
			for (Asteroid *asteroid : asteroids) {
				if (CheckCollision(bullet->GetRect(), asteroid->GetRect())) {
					asteroid->TakeDamage(bullet->GetDamage());
					bullet->SetCollision(true);
					if (asteroid->IsDead()) {
						score += asteroid->GetReward();
						int random = rand() % 101;
						if (random >= 95) {
							HealthDrop *healthDrop = new HealthDrop(asteroid->GetRect().x, asteroid->GetRect().y, 32, 32, renderer, new Vector2(64, 0));
							healthDrops.push_back(healthDrop);
						}
					}
				}
			}
		}

		for (HealthDrop *healthDrop : healthDrops) {
			if (CheckCollision(player->GetRect(), healthDrop->GetRect())) {
				player->RegenHealth(healthDrop->GetHealthAmount());
				healthDrop->SetCollision(true);
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

void Game::HandleBlinkingUnderscore(Nanoseconds deltaTime) {
	underscoreBlinkTime += deltaTime;
	if (underscoreBlinkTime >= underscoreBlinkInterval) {
		underscoreBlinkTime -= underscoreBlinkInterval;
		showUnderscore = showUnderscore ? false : true;
	}
}