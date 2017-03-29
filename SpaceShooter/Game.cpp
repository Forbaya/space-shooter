#include <SDL.h>
#include "InputHandler.h"
#include "Player.h"
#include "Game.h"

Game::Game() {
	player = new Player(16, 16);
	starField = new StarField(60);

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
	player->Move(axisInput->GetLeftX(), axisInput->GetLeftY());
	starField->Tick(axisInput);
}

void Game::Render(SDL_Surface *screen) {
	starField->Render(screen);
}