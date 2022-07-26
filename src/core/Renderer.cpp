#include "Renderer.h"

#include <sstream>
#include <iostream>
#include <algorithm>

Renderer::Renderer(SDL_Window* nativeWin)
{
	// Create render context
	m_context = SDL_CreateRenderer(nativeWin, -1, SDL_RENDERER_ACCELERATED);

	// If error initializing, throw error
	if (m_context == nullptr)
	{
		std::stringstream msg;
		msg << "ERROR: Failed to initialize renderer: " << SDL_GetError();
		throw msg.str();
	}

	m_renderQueue = new std::vector<std::tuple<Sprite*, const Transform*, int>>();
}

Renderer::~Renderer()
{
	delete m_renderQueue;
	SDL_DestroyRenderer(m_context);
}

SDL_Renderer* Renderer::GetRenderContext()
{
	return m_context;
}

void Renderer::EnqueueSprite(Sprite* sprite, const Transform& tf, int zind)
{
	m_renderQueue->push_back(std::tuple(sprite, &tf, zind));
}

void Renderer::Render(const Camera& camera)
{
	//Clear Buffer
	SDL_SetRenderDrawColor(m_context, 0, 0, 0, 255);
	SDL_RenderClear(m_context);

	//Sort by zind increasing
	std::sort(m_renderQueue->begin(), m_renderQueue->end(),
		[](std::tuple<Sprite*, const Transform*, int> a, std::tuple<Sprite*, const Transform*, int> b) {
			return std::get<2>(a) < std::get<2>(b);
		});

	for (auto& tuple : *m_renderQueue)
	{
		Sprite* sprite = std::get<0>(tuple);
		const Transform* tf = std::get<1>(tuple);
		//Get Frame Coords in World Space
		vec2 frameSize(sprite->GetWidth(), sprite->GetHeight());
		frameSize *= tf->scale;
		vec2 halfFrameSize = frameSize * 0.5f;
		vec2 frameOrigin(tf->position.x - halfFrameSize.x, tf->position.y + halfFrameSize.y); //Frame origin top left corner, not center
		vec2 frameEndCorner(tf->position.x + halfFrameSize.x, tf->position.y - halfFrameSize.y); //bottom-right corner

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
		SDL_RenderCopyEx(m_context, sprite->GetTexture(), NULL, &texrect, tf->rotation, NULL, SDL_FLIP_NONE);
	}

	//Swap Buffers
	SDL_RenderPresent(m_context);

	m_renderQueue->clear();
}
