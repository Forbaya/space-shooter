#include "Alien.h"

void Alien::Shoot(AxisInput *axisInput) {
	if (shotCooldownLeft <= zero) {
		Vector2 *direction = new Vector2(axisInput->GetRightX(), axisInput->GetRightY());
		int bulletSize = 6;
		Bullet *bullet = new Bullet(new Vector2(rect.x + rect.w / 2 - bulletSize / 2, rect.y + rect.h / 2 - bulletSize / 2),
									new Vector2(direction->GetX(), direction->GetY()), bulletSize, 6, 1);
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
