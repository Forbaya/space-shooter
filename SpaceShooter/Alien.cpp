#include "Alien.h"

Alien::Alien(int width, int height, SDL_Renderer *renderer, Vector2 *textureRegion)
		: Entity(width, height, renderer, textureRegion) {
}

Alien::~Alien() {
}

void Alien::Shoot(GamepadInput *gamepadInput) {
	if (gamepadInput->GetRightX() != 0 || gamepadInput->GetRightY() != 0) {
		if (shotCooldownLeft <= zeroNanoseconds) {
			Vector2 *direction = new Vector2(gamepadInput->GetRightX(), gamepadInput->GetRightY());
			int bulletSize = 6;
			Bullet *bullet = new Bullet(new Vector2(rect.x + rect.w / 2 - bulletSize / 2, rect.y + rect.h / 2 - bulletSize / 2),
										new Vector2(direction->GetX(), direction->GetY()), bulletSize, 6, 1);
			bullets.push_back(bullet);

			shotCooldownLeft = shotCooldown;
		}
	}
}

std::vector<Bullet*> Alien::GetBullets() {
	return bullets;
}

void Alien::SetDamage(int damage) {
	this->damage = damage;
}

int Alien::GetDamage() {
	return damage;
}
