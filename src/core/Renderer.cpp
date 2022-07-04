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

void Renderer::RenderSprite(Sprite* sprite, vec2 position, float rotation, float scale)
{
	float frameW = (float)sprite->GetWidth() * scale;
	float frameH = (float)sprite->GetHeight() * scale;
	vec2 frameOrigin; //Frame origin top left corner, not center
	frameOrigin.x = position.x - frameW * 0.5f;
	frameOrigin.y = position.y - frameH * 0.5f;
	SDL_Rect texrect;
	texrect.w = (int)frameW;
	texrect.h = (int)frameH;
	texrect.x = frameOrigin.x;
	texrect.y = frameOrigin.y;
	//Render to buffer
	SDL_RenderCopyEx(s_context, sprite->GetTexture(), NULL, &texrect, rotation, NULL, SDL_FLIP_NONE);
}

SDL_Renderer* Renderer::GetRenderContext()
{
	return s_context;
}
