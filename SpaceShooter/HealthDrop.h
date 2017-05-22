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
		bool GetCollision();
		void SetCollision(bool collision);
	private:
		int healthAmount;
		Nanoseconds currentFrameTime;
		Nanoseconds frameTime;
		int currentFrame;
		int NextFrame();
		bool collision;
};

#endif