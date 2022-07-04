#include "Sprite.h"

#include <SDL_image.h>

Sprite::Sprite(const std::string& filename, SDL_Renderer* renderContext)
{
	m_tex = IMG_LoadTexture(renderContext, filename.c_str());
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
