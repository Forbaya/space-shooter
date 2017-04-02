#include "Alien.h"

void Alien::Shoot(AxisInput * axisInput) {
	if (shotCooldownLeft <= noShotCooldown) {
		Vector2 *direction = new Vector2(axisInput->GetRightX(), axisInput->GetRightY());
		int bulletSize = 6;
		Bullet *bullet = new Bullet(new Vector2(position->GetX() + rect.w / 2 - bulletSize / 2, position->GetY() + rect.h / 2 - bulletSize / 2),
			new Vector2(direction->GetX(), direction->GetY()), bulletSize, 6);
		bullets.push_back(bullet);

		shotCooldownLeft = shotCooldown;
		currentTime = std::chrono::high_resolution_clock::now();
	}
	else {
		previousTime = currentTime;
		currentTime = std::chrono::high_resolution_clock::now();
		auto deltaTime = currentTime - previousTime;
		shotCooldownLeft -= std::chrono::duration_cast<std::chrono::nanoseconds>(deltaTime);
	}
}

std::vector<Bullet*> Alien::GetBullets() {
	return bullets;
}