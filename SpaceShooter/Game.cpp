#include "Player.h"
#include "Game.h"

Game::Game() {
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