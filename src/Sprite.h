#pragma once

#include <SDL.h>
#include <string>

class Sprite
{

private:
	SDL_Texture* m_tex;
	int m_width, m_height;

public:
	Sprite(SDL_Renderer* renderer, std::string imgpath);
	~Sprite();

	int GetWidth();
	int GetHeight();
	SDL_Texture* GetTexture();
};

