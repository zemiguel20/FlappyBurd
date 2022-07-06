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

void Renderer::RenderSprite(Sprite* sprite, const Transform& tf, const Camera& camera)
{
	//Get Frame Coords in World Space
	vec2 frameSize(sprite->GetWidth(), sprite->GetHeight());
	frameSize *= tf.scale;
	vec2 halfFrameSize = frameSize * 0.5f;
	vec2 frameOrigin(tf.position.x - halfFrameSize.x, tf.position.y + halfFrameSize.y); //Frame origin top left corner, not center
	vec2 frameEndCorner(tf.position.x + halfFrameSize.x, tf.position.y - halfFrameSize.y); //bottom-right corner

	//Convert to Viewport Space
	frameOrigin = camera.WorldToViewportPoint(frameOrigin);
	frameEndCorner = camera.WorldToViewportPoint(frameEndCorner);

	//Render frame
	SDL_Rect texrect;
	texrect.w = (int)(frameEndCorner.x - frameOrigin.x);
	texrect.h = (int)(frameEndCorner.y - frameOrigin.y);
	texrect.x = (int)frameOrigin.x;
	texrect.y = (int)frameOrigin.y;
	//Render to buffer
	SDL_RenderCopyEx(s_context, sprite->GetTexture(), NULL, &texrect, tf.rotation, NULL, SDL_FLIP_NONE);
}

SDL_Renderer* Renderer::GetRenderContext()
{
	return s_context;
}
