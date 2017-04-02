#ifndef ENTITY_H
#define ENTITY_H

#include <SDL_image.h>
#include <SDL.h>
#include <string>
#include "AxisInput.h"
#include "Vector2.h"

class Entity {
	public:
		SDL_Texture *texture;
		SDL_Rect rect;
		SDL_Point center;
		double rotation;
		Vector2 *position;
		std::chrono::nanoseconds frameTime;
		std::chrono::nanoseconds passedFrameTime;
		Time currentFrameTime;
		Time previousFrameTime;

		virtual void Tick(AxisInput *axisInput)=0;
		virtual void Move(int x, int y)=0;
		virtual void Render(SDL_Renderer *renderer)=0;

		SDL_Texture* LoadTexture(std::string path, SDL_Renderer *renderer);
		SDL_Rect GetRect();
		Vector2* GetPosition();
};

#endif