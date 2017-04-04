#include "Game.h"

Game::Game(SDL_Renderer *renderer) {
	this->renderer = renderer;

	srand(time(NULL));
	starField = new StarField(200);
	player = new Player(32, 32, renderer);
	Enemy *enemy = new Enemy(32, 32, renderer);
	enemies.push_back(enemy);
	Asteroid *asteroid = new Asteroid(32, 32, renderer);
	asteroids.push_back(asteroid);
	nextAsteroidSpawnTime = asteroid->GetNextSpawnTime();
	passedAsteroidSpawnTime = zero;

	running = true;

	currentTickTime = Clock::now();
}

Game::~Game() {
}

void Game::Start() {
	running = true;
}

void Game::Stop() {
	running = false;
}

bool Game::IsRunning() {
	return running;
}

Player* Game::GetPlayer() {
	return player;
}

StarField* Game::GetStarField() {
	return starField;
}

void Game::Tick(AxisInput *axisInput) {
	previousTickTime = currentTickTime;
	currentTickTime = Clock::now();
	auto deltaTime = currentTickTime - previousTickTime;

	passedAsteroidSpawnTime += std::chrono::duration_cast<Nanoseconds>(deltaTime);
	if (passedAsteroidSpawnTime >= nextAsteroidSpawnTime) {
		Asteroid *asteroid = new Asteroid(32, 32, renderer);
		asteroids.push_back(asteroid);
		this->nextAsteroidSpawnTime = asteroid->GetNextSpawnTime();
		passedAsteroidSpawnTime -= nextAsteroidSpawnTime;
	}

	starField->Tick(axisInput);
	player->Tick(axisInput);
	for (Enemy *enemy : enemies) {
		enemy->Tick(axisInput);
	}
	for (Asteroid *asteroid : asteroids) {
		asteroid->Tick(axisInput);
	}

	for (Enemy *enemy : enemies) {
		if (CheckCollision(player->GetRect(), enemy->GetRect())) {
			player->TakeDamage(enemy->GetDamage());
		}
	}

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
	for (Asteroid *asteroid : asteroids) {
		if (CheckCollision(asteroid->GetRect(), player->GetRect())) {
			asteroid->TakeDamage(asteroid->GetHealth());
			player->TakeDamage(asteroid->GetDamage());
		}
		//for (Asteroid *anotherAsteroid : asteroids) {
		//	if (asteroid != anotherAsteroid && CheckCollision(asteroid->GetRect(), anotherAsteroid->GetRect())) {
		//		asteroid->TakeDamage(asteroid->GetHealth());
		//		anotherAsteroid->TakeDamage(anotherAsteroid->GetHealth());
		//	}
		//}
	}

	enemies.erase(
		std::remove_if(
			enemies.begin(), enemies.end(),
			[](Enemy *enemy) {
				return enemy->IsDead();
			}
		),
		enemies.end()
	);

	asteroids.erase(
		std::remove_if(
			asteroids.begin(), asteroids.end(),
			[](Asteroid *asteroid) {
				return asteroid->GetRect().x < -SCREEN_WIDTH * 3 || asteroid->GetRect().x > SCREEN_WIDTH * 3 ||
						asteroid->GetRect().y < -SCREEN_HEIGHT * 3 || asteroid->GetRect().y > SCREEN_HEIGHT * 3 || asteroid->IsDead();
			}
		),
		asteroids.end()
	);
}

void Game::Render() {
	starField->Render(renderer);
	for (Asteroid *asteroid : asteroids) {
		asteroid->Render(renderer);
	}
	for (Enemy *enemy : enemies) {
		enemy->Render(renderer);
	}
	player->Render(renderer);
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
