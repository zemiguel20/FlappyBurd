#include "Renderer.h"

#include <sstream>
#include <iostream>

SDL_Renderer* Renderer::s_context = nullptr;

void Renderer::Init(SDL_Window* nativeWin)
{
	// Skip initialization if render context already created
	if (s_context != nullptr)
	{
		std::cout
			<< "Renderer already initialized. Skipping action."
			<< std::endl;
		return;
	}

	// Create render context
	s_context = SDL_CreateRenderer(nativeWin, -1, SDL_RENDERER_ACCELERATED);

	// If error initializing, throw error
	if (s_context == nullptr)
	{
		std::stringstream msg;
		msg << "ERROR: Failed to initialize renderer: " << SDL_GetError();
		throw msg.str();
	}
}

void Renderer::Destroy()
{
	SDL_DestroyRenderer(s_context);
}

void Renderer::ClearBuffer()
{
	SDL_SetRenderDrawColor(s_context, 0, 0, 0, 255);
	SDL_RenderClear(s_context);
}

void Renderer::SwapBuffers()
{
	SDL_RenderPresent(s_context);
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
	SDL_RenderCopy(s_context, sprite->GetTexture(), NULL, &texrect);
}

SDL_Renderer* Renderer::GetRenderContext()
{
	return s_context;
}
