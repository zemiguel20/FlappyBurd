#pragma once

#include <SDL.h>
#include "Sprite.h"
#include "Transform.h"
#include "Camera.h"
#include "Math.h"

#include <vector>
#include <tuple>

class Renderer
{
private:
	SDL_Renderer* m_context;
	std::vector<std::tuple<Sprite*, const Transform*, int>>* m_renderQueue;
public:
	/* @brief Should be called once at the start.
	* Make sure target window is initialized first.
	*
	* @param nativeWin - window render target
	*/
	Renderer(SDL_Window* nativeWin);
	~Renderer();

	SDL_Renderer* GetRenderContext();

	void EnqueueSprite(Sprite* sprite, const Transform& tf, int zind);
	void Render(const Camera& camera);
};

