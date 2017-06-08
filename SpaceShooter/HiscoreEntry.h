#ifndef RANK_H
#define RANK_H

#include <SDL_ttf.h>
#include <SDL.h>
#include <string>

class HiscoreEntry {
	public:
		HiscoreEntry(SDL_Renderer *renderer, int rank, std::string playerName, std::string date, std::string score);
		~HiscoreEntry();
		void Render();
		SDL_Texture *LoadTextTexture(std::string text, SDL_Color textColor, SDL_Renderer * renderer);
		int CountDigitsInInteger(int x);
	private:
		SDL_Renderer *renderer;
		int rank;
		SDL_Rect rankRect;
		SDL_Rect playerNameRect;
		SDL_Rect dateRect;
		SDL_Rect scoreRect;
		SDL_Texture *rankTexture;
		SDL_Texture *playerNameTexture;
		SDL_Texture *dateTexture;
		SDL_Texture *scoreTexture;
		TTF_Font *font;
		SDL_Color white;
		SDL_Color gold;
		SDL_Color silver;
		SDL_Color bronze;
};

#endif
