#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <chrono>

typedef std::chrono::time_point<std::chrono::steady_clock, std::chrono::duration<__int64, std::ratio<1, 1000000000>>> Time;
typedef std::chrono::high_resolution_clock Clock;
typedef std::chrono::nanoseconds Nanoseconds;

const int SCREEN_WIDTH = 720;
const int SCREEN_HEIGHT = 480;
const float STAR_MINIMUM_SPEED = 1.2f;
const float STAR_MIDDLE_SPEED = 0.8f;
const float STAR_MAXIMUM_SPEED = 0.5f;

const Nanoseconds zeroNanoseconds = Nanoseconds(0);

enum MovementSpeed {
	NO_SPEED = 0, SLOW_SPEED = 1, AVERAGE_SPEED = 2, FAST_SPEED = 3, REALLY_FAST_SPEED = 4
};

enum Border {
	TOP = 0, LEFT = 1, BOTTOM = 2, RIGHT = 3
};

enum MainMenuButtons {
	// NEW_GAME, HISCORES, INSTRUCTIONS, OPTIONS, QUIT
	NEW_GAME, HISCORES, INSTRUCTIONS, QUIT
};

enum HiscoreButtons {
	BACK, RESET_HISCORES
};

enum Screens {
	MAIN_MENU_SCREEN, GAME_SCREEN, HISCORES_SCREEN, INSTRUCTIONS_SCREEN
};

#endif
