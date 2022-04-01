#include "Sprite.h"

Sprite::Sprite(SDL_Texture* texture, int width, int height)
{
	m_tex = texture;
	m_width = width;
	m_height = height;
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
