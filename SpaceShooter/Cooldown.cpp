#include "Cooldown.h"

Cooldown::Cooldown(Nanoseconds length, bool onCooldown) {
	this->cooldownLength = length;
	this->cooldownLeft = onCooldown ? length : zeroNanoseconds;
	bool kappa123 = true;
}

Cooldown::~Cooldown() {
}

void Cooldown::Tick(Nanoseconds deltaTime) {
	this->cooldownLeft -= deltaTime;
}

bool Cooldown::OnCooldown() {
	return cooldownLeft > zeroNanoseconds;
}

Nanoseconds Cooldown::GetCooldownLeft() {
	return cooldownLeft;
}

void Cooldown::PutOnCooldown() {
	this->cooldownLeft = cooldownLength;
}
