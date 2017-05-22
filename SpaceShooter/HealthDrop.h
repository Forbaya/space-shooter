#ifndef HEALTHDROP_H
#define HEALTHDROP_H

#include <SDL.h>
#include "Entity.h"
#include "Vector2.h"

class HealthDrop : public Entity {
	public:
		HealthDrop(int x, int y, int width, int height, SDL_Renderer *renderer, Vector2 *textureRegion);
		~HealthDrop();
		void Tick(Inputs *inputs);
		void Move(int x, int y);
		void ChangeAnimationFrame();
		void Render(SDL_Renderer *renderer);
		int GetHealthAmount();
		bool GetDeletable();
		void SetDeletable(bool deletable);
	private:
		int healthAmount;
		Nanoseconds currentFrameTime;
		Nanoseconds frameTime;
		Nanoseconds currentAliveTime;
		Nanoseconds aliveTime;
		Nanoseconds currentBlinkTime;
		Nanoseconds blinkTime;
		Nanoseconds blinkInterval;
		int currentFrame;
		int NextFrame();
		bool deletable;
		bool show;
};

#endif