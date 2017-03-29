#ifndef CONSTANTS_H
#define CONSTANTS_H

const int SCREEN_WIDTH = 720;
const int SCREEN_HEIGHT = 480;
const float STAR_MINIMUM_SPEED = 1.2f;
const float STAR_MIDDLE_SPEED = 0.8f;
const float STAR_MAXIXMUM_SPEED = 0.5f;

enum MovementSpeed {
	NO_SPEED = 0, SLOW_SPEED = 1, AVERAGE_SPEED = 2, FAST_SPEED = 3, REALLY_FAST_SPEED = 4
};

#endif