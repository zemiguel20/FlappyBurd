#pragma once

#include <SDL.h>

class Sprite
{
private:
	SDL_Texture* m_tex;
	int m_width, m_height;

public:
	Sprite(SDL_Texture* texture);
	~Sprite();

	int GetWidth();
	int GetHeight();
	SDL_Texture* GetTexture();
};