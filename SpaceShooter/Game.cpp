#include "Game.h"

Game::Game(SDL_Renderer *renderer) {
	this->renderer = renderer;

	srand(time(NULL));
	starField = new StarField(200);
	player = new Player(32, 32, renderer);
	enemy = new Enemy(32, 32, renderer);
	asteroid = new Asteroid(32, 32, renderer);
	asteroids.push_back(asteroid);

	running = true;
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
	starField->Tick(axisInput);
	player->Tick(axisInput);
	enemy->Tick(axisInput);
	for (Asteroid *asteroid : asteroids) {
		asteroid->Tick(axisInput);
	}
	if (CheckCollision(player->GetRect(), enemy->GetRect())) {
		player->TakeDamage(enemy->GetDamage());
		printf("Player health: %d\n", player->GetHealth());
	}
	std::vector<Bullet*> playerBullets = player->GetBullets();
	for (Bullet *bullet : playerBullets) {
		if (CheckCollision(bullet->GetRect(), enemy->GetRect())) {
			enemy->TakeDamage(bullet->GetDamage());
			bullet->SetCollision(true);
		} else if (CheckCollision(bullet->GetRect(), asteroid->GetRect())) {
			asteroid->TakeDamage(bullet->GetDamage());
			bullet->SetCollision(true);
		}
	}
	for (Asteroid *asteroid : asteroids) {
		if (CheckCollision(asteroid->GetRect(), player->GetRect())) {
			asteroid->TakeDamage(asteroid->GetHealth());
			player->TakeDamage(asteroid->GetDamage());
		}
	}
}

void Game::Render() {
	starField->Render(renderer);
	asteroid->Render(renderer);
	enemy->Render(renderer);
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
