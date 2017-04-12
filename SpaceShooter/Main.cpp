#include <chrono>
#include <iostream>
#include <math.h> 
#include <SDL_image.h>
#include <SDL.h>
#include <stdio.h>
#include <stdio.h>
#include <string>
#include "Constants.h"
#include "InputHandler.h"
#include "Game.h"
#include "MainMenu.h"
#include "Player.h"

using namespace std::chrono_literals;

SDL_Window *window;
SDL_Renderer *renderer;
SDL_GameController *controller;
Game *game;
MainMenu *mainMenu;
InputHandler *inputHandler;
SDL_Event e;
Screen *screen;

bool Initialize();
void Run();
void Tick();
void Close();
void Render();
void HandleInput(SDL_Event e);

/* Initializes SDL. */
bool Initialize() {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER)) {
		printf("SDL Couldn't be initialized! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	window = SDL_CreateWindow("Space shooter!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (window == NULL) {
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		printf("Renderer couldn't be created! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
		printf("SDL_image couldn't initialize! SDL_image error: %s\n", IMG_GetError());
		return false;
	}

	if (TTF_Init() == -1) {
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		return false;
	}

	game = new Game(renderer);
	mainMenu = new MainMenu(renderer);
	screen = &(*mainMenu);
	inputHandler = new InputHandler();

	for (int i = 0; i < SDL_NumJoysticks(); i++) {
		if (SDL_IsGameController(i)) {
			controller = SDL_GameControllerOpen(i);
			if (!controller) {
				fprintf(stderr, "Could not open gamecontroller %i: %s\n", i, SDL_GetError());
			}
		}
	}

	return true;
}

/* The game loop. */
void Run() {
	int ticks = 0;
	int frames = 0;
	int targetTicksPerSecond = 60;
	Nanoseconds nsPerTick(1000000000 / targetTicksPerSecond);
	Nanoseconds lag(0);
	Nanoseconds time(0);

	auto previousTime = Clock::now();

	while (screen->IsRunning()) {
		auto currentTime = Clock::now();
		auto deltaTime = currentTime - previousTime;
		previousTime = currentTime;
		lag += std::chrono::duration_cast<Nanoseconds>(deltaTime);
		time += std::chrono::duration_cast<Nanoseconds>(deltaTime);

		if (SDL_PollEvent(&e) != 0) {
			HandleInput(e);
		}

		while (lag >= nsPerTick) {
			Tick();
			ticks++;
			lag -= nsPerTick;
		}

		Render();
		frames++;

		if (time >= Nanoseconds(1000000000)) {
			printf("Frames: %d, Ticks: %d\n", frames, ticks);
			ticks = 0;
			frames = 0;
			time = zeroNanoseconds;
		}
	}
}

void HandleInput(SDL_Event e) {
	inputHandler->HandleInput(e, game);
}

void Render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	screen->Render();
	SDL_RenderPresent(renderer);
}

/* Updates the game world. */
void Tick() {
	int nextScreen = screen->GetNextScreen();
	if (nextScreen != -1) {
		if (nextScreen == GAME_SCREEN) {
			inputHandler->SetScreen(nextScreen);
			screen = &(*new Game(renderer));
		}
	}

	screen->Tick(inputHandler->GetGamepadInput(), inputHandler->GetKeyboardInput());
}

/* Closes the window. */
void Close() {
	delete game;
	delete inputHandler;

	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char *args[]) {
	if (!Initialize()) {
		printf("Could not initialize!\n");
		return -1;
	}

	srand(time(NULL));
	Run();

	Close();
	return 0;
}