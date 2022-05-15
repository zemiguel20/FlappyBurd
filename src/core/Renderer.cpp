#include "Renderer.h"

#include <sstream>
#include <iostream>

Renderer* Renderer::instance = nullptr;

void Renderer::Init(SDL_Window* nativeWin)
{
	if (instance != nullptr)
	{
		std::cout
			<< "Renderer already initialized. Skipping action."
			<< std::endl;
		return;
	}

	instance = new Renderer;

	instance->m_context =
		SDL_CreateRenderer(nativeWin, -1, SDL_RENDERER_ACCELERATED);

	if (instance->m_context == nullptr)
	{
		std::stringstream msg;
		msg << "ERROR: Failed to initialize renderer: " << SDL_GetError();
		throw msg.str();
	}
}

void Renderer::Destroy()
{
	SDL_DestroyRenderer(instance->m_context);
	delete instance;
}

void Renderer::ClearBuffer()
{
	SDL_SetRenderDrawColor(instance->m_context, 0, 0, 0, 255);
	SDL_RenderClear(instance->m_context);
}

void Renderer::SwapBuffers()
{
	SDL_RenderPresent(instance->m_context);
}

void Renderer::RenderSprite(Sprite* sprite, float x, float y, float scale)
{
	SDL_Rect texrect;

	//Set img size with scale
	texrect.w = sprite->GetWidth() * scale;
	texrect.h = sprite->GetHeight() * scale;

	//Rect origin is img top left corner, subtract half img size for center
	texrect.x = x - (texrect.w / 2);
	texrect.y = y - (texrect.h / 2);

	//Render to buffer
	SDL_RenderCopy(instance->m_context, sprite->GetTexture(), NULL, &texrect);
}

SDL_Renderer* Renderer::GetRenderContext()
{
	return instance->m_context;
}
