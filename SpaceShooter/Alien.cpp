#include "Alien.h"

Alien::Alien(int width, int height, SDL_Renderer *renderer, Vector2 *textureRegion, long *gameScore)
		: Entity(width, height, renderer, textureRegion, gameScore) {
}

Alien::~Alien() {
}

void Alien::Shoot(Inputs *inputs) {
	int bulletSize = 6;

	if ((inputs->GetGamepadInput()->GetRightX() != 0 || inputs->GetGamepadInput()->GetRightY() != 0) && shotCooldownLeft <= zeroNanoseconds) {
		Vector2 *direction = new Vector2(inputs->GetGamepadInput()->GetRightX(), inputs->GetGamepadInput()->GetRightY());
		
		Bullet *bullet = new Bullet(new Vector2(rect.x + rect.w / 2 - bulletSize / 2, rect.y + rect.h / 2 - bulletSize / 2),
									new Vector2(direction->GetX(), direction->GetY()), bulletSize, 6, 1, NULL);
		bullets.push_back(bullet);
		delete direction;

		shotCooldownLeft = shotCooldown;
	} else if ((inputs->GetKeyboardInput()->GetArrowUp() || inputs->GetKeyboardInput()->GetArrowRight() || inputs->GetKeyboardInput()->GetArrowLeft() ||
				inputs->GetKeyboardInput()->GetArrowDown()) && shotCooldownLeft <= zeroNanoseconds) {
		int x = 0;
		int y = 0;

		if (inputs->GetKeyboardInput()->GetArrowUp()) {
			y = -1;
		}
		if (inputs->GetKeyboardInput()->GetArrowRight()) {
			x = 1;
		}
		if (inputs->GetKeyboardInput()->GetArrowLeft()) {
			x = -1;
		}
		if (inputs->GetKeyboardInput()->GetArrowDown()) {
			y = 1;
		}

		Bullet *bullet = new Bullet(new Vector2(rect.x + rect.w / 2 - bulletSize / 2, rect.y + rect.h / 2 - bulletSize / 2), 
									new Vector2(x, y), bulletSize, 6, 1, NULL);
		bullets.push_back(bullet);

		shotCooldownLeft = shotCooldown;
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
