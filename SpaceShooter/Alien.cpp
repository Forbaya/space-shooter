#include "Alien.h"

Alien::Alien(int width, int height, SDL_Renderer *renderer, Vector2 *textureRegion, long *gameScore)
		: Entity(width, height, renderer, textureRegion, gameScore) {
}

Alien::~Alien() {
}

void Alien::Shoot(Inputs *inputs) {
	if (inputs->GetGamepadInput()->GetRightX() != 0 || inputs->GetGamepadInput()->GetRightY() != 0) {
		if (shotCooldownLeft <= zeroNanoseconds) {
			Vector2 *direction = new Vector2(inputs->GetGamepadInput()->GetRightX(), inputs->GetGamepadInput()->GetRightY());
			int bulletSize = 6;
			Bullet *bullet = new Bullet(new Vector2(rect.x + rect.w / 2 - bulletSize / 2, rect.y + rect.h / 2 - bulletSize / 2),
										new Vector2(direction->GetX(), direction->GetY()), bulletSize, 6, 1, NULL);
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
