#include <SDL.h>
#include "Player.h"
#include "Game.h"

Game::Game() {
	player = new Player(16, 16);
	starField = new StarField(50);

	running = true;
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

void Game::Tick() {

}

void Game::Render(SDL_Surface *screen) {
	starField->Render(screen);
}