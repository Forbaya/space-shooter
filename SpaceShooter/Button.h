#ifndef BUTTON_H
#define BUTTON_H

#include <SDL_ttf.h>
#include <SDL.h>
#include <string>

class Button {
	public:
		Button(int buttonId, SDL_Renderer *renderer, std::string text, SDL_Rect rect, bool selected);
		~Button();
		SDL_Texture* GetTexture();
		void LoadTexture(std::string text, SDL_Color textColor);
		void Render();
		std::string GetText();
	private:
		int buttonId;
		SDL_Texture *texture;
		TTF_Font *font;
		SDL_Rect rect;
		SDL_Color white;
		SDL_Color selectedColor;
		SDL_Color color;
		std::string text;
		SDL_Renderer *renderer;
		bool selected;
};

#endif
