#pragma once

#include <SDL.h>
#include "Sprite.h"

/* @brief Static 2D renderer class.
* Interface to manage a static renderer instance.
*/
class Renderer
{
private:
	static Renderer* instance;

public:
	/* @brief Initializes the renderer static instance.
	* Should be called once at the start.
	* Make sure target window is initialized first.
	*
	* @param nativeWin - window render target
	*/
	static void Init(SDL_Window* nativeWin);

	/* @brief Destroys renderer and cleanup.
	* Should be called at the end.
	*/
	static void Destroy();

	/* @brief Clears render buffer by overriding with black color. */
	static void ClearBuffer();

	/* @brief Swap front and back render buffers. */
	static void SwapBuffers();

	//TODO: add proper transform
	static void RenderSprite(Sprite& sprite, float x, float y, float scale);

	static SDL_Renderer* GetRenderContext();

	/* Renderer properties */
private:
	SDL_Renderer* m_context;
};

