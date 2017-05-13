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

	pauseTexture = LoadTextTexture("PAUSED", { 255, 255, 255 }, renderer);
	youDiedTexture = LoadTextTexture("YOU DIED!", { 255, 255, 255 }, renderer);
	scoreTexture = LoadTextTexture(std::to_string(score), { 255, 255, 255 }, renderer);
	healthTextTexture = LoadTextTexture("Health", { 255, 255, 255 }, renderer);
	scoreTextTexture = LoadTextTexture("Score", { 255, 255, 255 }, renderer);

	playerName = "";

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


			/*if (players.empty() && (inputs->GetGamepadInput()->GetButtonA() || inputs->GetKeyboardInput()->GetButtonEnter() ||
			inputs->GetKeyboardInput()->GetButtonEsc())) {
			SetNextScreen(MAIN_MENU_SCREEN);
			}*/

			if (players.size() == 0) {
				healthLeftRect = { 20, 50, 0, 30 };
			} else {
				healthLeftRect = { 20, 50, players.at(0)->GetHealth() * 30, 30 };
			}

		}
	} else {
		textCooldownLeft += std::chrono::duration_cast<Nanoseconds>(deltaTime);

		if (textCooldownLeft >= textCooldown) {
			if (inputs->GetKeyboardInput()->GetButtonQ()) {
				playerName += "Q";
				textCooldownLeft = zeroNanoseconds;
			}
			if (inputs->GetKeyboardInput()->GetButtonW()) {
				playerName += "W";
				textCooldownLeft = zeroNanoseconds;
			}
			if (inputs->GetKeyboardInput()->GetButtonE()) {
				playerName += "E";
				textCooldownLeft = zeroNanoseconds;
			}
			if (inputs->GetKeyboardInput()->GetButtonR()) {
				playerName += "R";
				textCooldownLeft = zeroNanoseconds;
			}
			if (inputs->GetKeyboardInput()->GetButtonT()) {
				playerName += "T";
				textCooldownLeft = zeroNanoseconds;
			}
			if (inputs->GetKeyboardInput()->GetButtonY()) {
				playerName += "Y";
				textCooldownLeft = zeroNanoseconds;
			}
			if (inputs->GetKeyboardInput()->GetButtonU()) {
				playerName += "U";
				textCooldownLeft = zeroNanoseconds;
			}
			if (inputs->GetKeyboardInput()->GetButtonI()) {
				playerName += "I";
				textCooldownLeft = zeroNanoseconds;
			}
			if (inputs->GetKeyboardInput()->GetButtonO()) {
				playerName += "O";
				textCooldownLeft = zeroNanoseconds;
			}
			if (inputs->GetKeyboardInput()->GetButtonP()) {
				playerName += "P";
				textCooldownLeft = zeroNanoseconds;
			}
			if (inputs->GetKeyboardInput()->GetButtonA()) {
				playerName += "A";
				textCooldownLeft = zeroNanoseconds;
			}
			if (inputs->GetKeyboardInput()->GetButtonS()) {
				playerName += "S";
				textCooldownLeft = zeroNanoseconds;
			}
			if (inputs->GetKeyboardInput()->GetButtonD()) {
				playerName += "D";
				textCooldownLeft = zeroNanoseconds;
			}
			if (inputs->GetKeyboardInput()->GetButtonF()) {
				playerName += "F";
				textCooldownLeft = zeroNanoseconds;
			}
			if (inputs->GetKeyboardInput()->GetButtonG()) {
				playerName += "G";
				textCooldownLeft = zeroNanoseconds;
			}
			if (inputs->GetKeyboardInput()->GetButtonH()) {
				playerName += "H";
				textCooldownLeft = zeroNanoseconds;
			}
			if (inputs->GetKeyboardInput()->GetButtonJ()) {
				playerName += "J";
				textCooldownLeft = zeroNanoseconds;
			}
			if (inputs->GetKeyboardInput()->GetButtonK()) {
				playerName += "K";
				textCooldownLeft = zeroNanoseconds;
			}
			if (inputs->GetKeyboardInput()->GetButtonL()) {
				playerName += "L";
				textCooldownLeft = zeroNanoseconds;
			}
			if (inputs->GetKeyboardInput()->GetButtonZ()) {
				playerName += "Z";
				textCooldownLeft = zeroNanoseconds;
			}
			if (inputs->GetKeyboardInput()->GetButtonX()) {
				playerName += "X";
				textCooldownLeft = zeroNanoseconds;
			}
			if (inputs->GetKeyboardInput()->GetButtonC()) {
				playerName += "C";
				textCooldownLeft = zeroNanoseconds;
			}
			if (inputs->GetKeyboardInput()->GetButtonV()) {
				playerName += "V";
				textCooldownLeft = zeroNanoseconds;
			}
			if (inputs->GetKeyboardInput()->GetButtonB()) {
				playerName += "B";
				textCooldownLeft = zeroNanoseconds;
			}
			if (inputs->GetKeyboardInput()->GetButtonN()) {
				playerName += "N";
				textCooldownLeft = zeroNanoseconds;
			}
			if (inputs->GetKeyboardInput()->GetButtonM()) {
				playerName += "M";
				textCooldownLeft = zeroNanoseconds;
			}
			std::cout << "Player name: " << playerName << std::endl;
		}

		
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
