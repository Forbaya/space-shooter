#include <SDL.h>

#include "Constants.h"
#include "Player.h"
#include "InputHandler.h"

Player::Player(int width, int height) {
	rect.x = SCREEN_WIDTH / 2 - 32;
	rect.y = SCREEN_HEIGHT / 2 - 32;
	rect.w = 16;
	rect.h = 16;
}

SDL_Rect Player::GetRect() {
	return rect;
}

void Player::Tick() {

}

void Player::Move(int x, int y) {
	rect.x += x;
	if (rect.x < 0) rect.x = 0;
	if (rect.x > SCREEN_WIDTH - 16) rect.x = SCREEN_WIDTH - 16;

	rect.y += y;
	if (rect.y < 0) rect.y = 0;
	if (rect.y > SCREEN_HEIGHT - 16) rect.y = SCREEN_HEIGHT - 16;
}