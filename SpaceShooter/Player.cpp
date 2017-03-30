#include <SDL.h>
#include "AxisInput.h"
#include "Bullet.h"
#include "Constants.h"
#include "Player.h"
#include "InputHandler.h"

Player::Player(int width, int height) {
	position = new Vector2(SCREEN_WIDTH / 2 - 32, SCREEN_HEIGHT / 2 - 32);
	rect.x = SCREEN_WIDTH / 2 - 32;
	rect.y = SCREEN_HEIGHT / 2 - 32;
	rect.w = 16;
	rect.h = 16;
}

Player::~Player() {
}

SDL_Rect Player::GetRect() {
	return rect;
}

void Player::Tick(AxisInput *axisInput) {
	if (axisInput->GetRightX() != 0 || axisInput->GetRightY() != 0) {
		Shoot(axisInput);
	}

	Move(axisInput->GetLeftX(), axisInput->GetLeftY());

	for (Bullet *bullet : bullets) {
		bullet->Tick(axisInput);
		//if (bullet->GetPosition()->GetX() < -SCREEN_WIDTH * 3 || bullet->GetPosition()->GetX() > SCREEN_WIDTH * 3 ||
		//	bullet->GetPosition()->GetY() < -SCREEN_HEIGHT * 3 || bullet->GetPosition()->GetY() > SCREEN_HEIGHT * 3) {
		//	bullets.remove
		//	delete bullet;
		//	
		//}
	}
}

void Player::Move(int x, int y) {
	rect.x += x;
	position->SetX(position->GetX() + x);
	if (rect.x < 0) {
		rect.x = 0;
		position->SetX(0);
	}
	if (rect.x > SCREEN_WIDTH - 16) {
		rect.x = SCREEN_WIDTH - 16;
		position->SetX(SCREEN_WIDTH - 16);
	}
	rect.y += y;
	position->SetY(position->GetY() + y);
	if (rect.y < 0) {
		rect.y = 0;
		position->SetY(0);
	}
	if (rect.y > SCREEN_HEIGHT - 16) {
		rect.y = SCREEN_HEIGHT - 16;
		position->SetY(SCREEN_HEIGHT - 16);
	}
}

void Player::Shoot(AxisInput *axisInput) {
	//printf("Shooting\n");
	Vector2 *direction = new Vector2(axisInput->GetRightX(), axisInput->GetRightY());
	Bullet *bullet = new Bullet(position, direction, 5, 2);
	bullets.push_back(bullet);
}

std::vector<Bullet*> Player::GetBullets() {
	return bullets;
}

void Player::Render(SDL_Surface *screen) {
	for (Bullet *bullet : bullets) {
		bullet->Render(screen);
	}
	SDL_FillRect(screen, &GetRect(), SDL_MapRGB(screen->format, 255, 0, 0));
}