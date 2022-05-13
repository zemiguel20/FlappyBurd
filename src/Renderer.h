#pragma once

#include <SDL.h>
#include "Sprite.h"

class Renderer
{
private:
	SDL_Renderer* m_context;
public:
	Renderer();
	~Renderer();

	void Init(SDL_Window* nativeWin);
	void ClearBuffer();
	void SwapBuffers();

	//TODO: add proper transform
	void RenderSprite(Sprite& sprite, float x, float y, float scale);

	SDL_Renderer* GetRenderContext();
};

