#include <SDL.h>
#include "InputHandler.h"
#include "Player.h"
#include "Game.h"

Game::Game(SDL_Renderer *renderer) {
	this->renderer = renderer;
	player = new Player(32, 32);
	player->LoadTexture("res/spritesheet.png", renderer);
	
	starField = new StarField(200);
	enemy = new Enemy(32, 32);
	enemy->LoadTexture("res/spritesheet.png", renderer);
	SDL_SetTextureColorMod(enemy->GetTexture(), 255, 128, 255);
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
	player->Tick(axisInput);
	enemy->Tick(axisInput);
	starField->Tick(axisInput);
	if (CheckCollision(player->GetRect(), enemy->GetRect())) {
		printf("Enemy collides with player!\n");
	}
	std::vector<Bullet*> playerBullets = player->GetBullets();
	for (Bullet *bullet : playerBullets) {
		if (CheckCollision(bullet->GetRect(), enemy->GetRect())) {
			printf("Bullet hits enemy!\n");
		}
	}
}

void Game::Render() {
	starField->Render(renderer);
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

	if (bottomA <= topB || topA >= bottomB || rightA <= leftB ||
		leftA >= rightB) {
		return false;
	}

	return true;
}