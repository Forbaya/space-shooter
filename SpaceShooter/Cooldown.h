#ifndef COOLDOWN_H
#define COOLDOWN_H

#include <chrono>
#include "Constants.h"

class Cooldown {
public:
	Cooldown(Nanoseconds length, bool onCooldown);
	~Cooldown();
	void Tick(Nanoseconds deltaTime);
	void PutOnCooldown();
	bool OnCooldown();
	Nanoseconds GetCooldownLeft();
	void SetCooldownLength(Nanoseconds newCooldownLength);
private:
	Nanoseconds cooldownLeft;
	Nanoseconds cooldownLength;
};

#endif
