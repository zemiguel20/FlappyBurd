#include "Sprite.h"

Sprite::Sprite(SDL_Texture* texture)
{
	m_tex = texture;
	// get the width and height of the texture
	SDL_QueryTexture(m_tex, NULL, NULL, &m_width, &m_height);
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
