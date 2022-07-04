#pragma once

#include <SDL.h>
#include <string>

class Sprite
{
private:
	SDL_Texture* m_tex;
	int m_width, m_height;

public:
	Sprite(const std::string& filename, SDL_Renderer* renderContext);
	~Sprite();

	int GetWidth();
	int GetHeight();
	SDL_Texture* GetTexture();
};