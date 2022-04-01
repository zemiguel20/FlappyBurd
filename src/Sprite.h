#pragma once

#include <SDL.h>

class Sprite
{
private:
	SDL_Texture* m_tex;
	int m_width, m_height;

public:
	Sprite(SDL_Texture* texture, int width, int height);
	~Sprite();

	int GetWidth();
	int GetHeight();
	SDL_Texture* GetTexture();
};