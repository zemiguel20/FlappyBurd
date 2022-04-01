#pragma once

#include <SDL.h>
#include "Window.h"
#include "Sprite.h"

class Renderer
{
private:
	SDL_Renderer* m_context;
public:
	Renderer();
	~Renderer();

	void Init(Window& win);
	void ClearBuffer();
	void SwapBuffers();

	//TODO: add proper transform
	void RenderSprite(Sprite& sprite, float x, float y, float scale);

	SDL_Renderer* GetRenderContext();
};

