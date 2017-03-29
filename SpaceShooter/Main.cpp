#include <chrono>
#include <iostream>
#include <math.h> 
#include <SDL.h>
#include <stdio.h>
#include "Constants.h"
#include "InputHandler.h"
#include "Game.h"
#include "Player.h"

using namespace std::chrono_literals;

SDL_Window *window = NULL;
SDL_Surface *screen = NULL;
SDL_GameController *controller = NULL;
Game *game = NULL;
InputHandler *inputHandler = NULL;
SDL_Event e;
Uint32 bgColor;

bool running;

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

	game = new Game();
	inputHandler = new InputHandler();

	screen = SDL_GetWindowSurface(window);
	running = true;
	bgColor = SDL_MapRGB(screen->format, 0, 0, 0);

	for (int i = 0; i < SDL_NumJoysticks(); i++) {
		if (SDL_IsGameController(i)) {
			controller = SDL_GameControllerOpen(i);
			if (controller) {
				break;
			}
			else {
				fprintf(stderr, "Could not open gamecontroller %i: %s\n", i, SDL_GetError());
			}
		}
	}

	return true;
}

/* The game loop. */
void Run() {
	using clock = std::chrono::high_resolution_clock;

	int ticks = 0;
	int frames = 0;
	int targetTicksPerSecond = 60;
	std::chrono::nanoseconds nsPerTick(1000000000 / targetTicksPerSecond);
	std::chrono::nanoseconds lag(0);
	std::chrono::nanoseconds time(0);

	auto previousTime = clock::now();

	while (game->IsRunning()) {
		auto currentTime = clock::now();
		auto deltaTime = currentTime - previousTime;
		previousTime = currentTime;
		lag += std::chrono::duration_cast<std::chrono::nanoseconds>(deltaTime);
		time += std::chrono::duration_cast<std::chrono::nanoseconds>(deltaTime);

		if (SDL_PollEvent(&e) != 0) {
			HandleInput(e);
		}

		while (lag >= nsPerTick) {
			lag -= nsPerTick;

			Tick();
			ticks++;
		}

		Render();
		frames++;

		if (time >= std::chrono::nanoseconds(1000000000)) {
			printf("Frames: %d, Ticks: %d\n", frames, ticks);
			ticks = 0;
			frames = 0;
			time = std::chrono::nanoseconds(0);
		}
	}
}

void HandleInput(SDL_Event e) {
	inputHandler->HandleInput(e, game);
}

void Render() {
	SDL_FillRect(screen, NULL, bgColor);
	game->Render(screen);
	SDL_FillRect(screen, &game->GetPlayer()->GetRect(), SDL_MapRGB(screen->format, 255, 0, 0));
	SDL_UpdateWindowSurface(window);
}

/* Updates the game world. */
void Tick() {
	game->Tick(inputHandler->GetAxisInput());
	//printf("x: %d, y: %d\n", inputHandler->GetRightXValue(), inputHandler->GetRightYValue());
	double x = (double) inputHandler->GetRightXValue();
	double y = (double) inputHandler->GetRightYValue();
	double slope = 0;
	if (x != 0) {
		slope = y / x;
	}
	//printf("x: %f, y: %f, slope: %f\n", x, y, slope);
}

/* Closes the window. */
void Close() {
	delete game;
	delete inputHandler;

	SDL_DestroyWindow(window);
	window = NULL;

	SDL_Quit();
}

int main(int argc, char *args[]) {
	if (!Initialize()) {
		printf("Could not initialize!\n");
		return -1;
	}
	SDL_UpdateWindowSurface(window);

	Run();

	Close();
	return 0;
}