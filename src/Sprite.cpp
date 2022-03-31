#include "Sprite.h"

#include <SDL_image.h>

Sprite::Sprite(SDL_Renderer* renderer, std::string imgpath)
{
	m_tex = IMG_LoadTexture(renderer, imgpath.c_str());
	SDL_QueryTexture(m_tex, NULL, NULL, &m_width, &m_height); // get the width and height of the texture
}

Sprite::~Sprite()
{
	SDL_DestroyTexture(m_tex);
}

int Sprite::GetWidth()
{
	return m_width;
}

int Sprite::GetHeight()
{
	return m_height;
}

SDL_Texture* Sprite::GetTexture()
{
	return m_tex;
}
