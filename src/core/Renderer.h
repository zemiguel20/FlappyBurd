#pragma once

#include <SDL.h>
#include "Sprite.h"
#include "Math.h"

/* @brief Static 2D renderer class.
*/
class Renderer
{
private:
	static SDL_Renderer* s_context;

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

	static void RenderSprite(Sprite* sprite, vec2 position, float rotation, float scale);

	static SDL_Renderer* GetRenderContext();
};

