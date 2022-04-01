#include "Renderer.h"

#include <sstream>
#include <iostream>

Renderer::Renderer()
{
	m_context = nullptr;
}

Renderer::~Renderer()
{
	SDL_DestroyRenderer(m_context);
}

void Renderer::Init(Window& win)
{
	m_context = SDL_CreateRenderer(win.GetNativeWindow(), -1, SDL_RENDERER_ACCELERATED);
	if (m_context == nullptr)
	{
		std::stringstream msg;
		msg << "ERROR: Failed to initialize renderer: " << SDL_GetError();
		throw msg.str();
	}
}

void Renderer::ClearBuffer()
{
	SDL_SetRenderDrawColor(m_context, 0, 0, 0, 255);
	SDL_RenderClear(m_context);
}

void Renderer::SwapBuffers()
{
	SDL_RenderPresent(m_context);
}

void Renderer::RenderSprite(Sprite& sprite, float x, float y, float scale)
{
	SDL_Rect texrect;

	//Set img size with scale
	texrect.w = sprite.GetWidth() * scale;
	texrect.h = sprite.GetHeight() * scale;

	//Rect origin is img top left corner, subtract half img size for center
	texrect.x = x - (texrect.w / 2);
	texrect.y = y - (texrect.h / 2);

	//Render to buffer
	SDL_RenderCopy(m_context, sprite.GetTexture(), NULL, &texrect);
}

SDL_Renderer* Renderer::GetRenderContext()
{
	return m_context;
}
