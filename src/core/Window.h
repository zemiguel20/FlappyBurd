#pragma once

#include <SDL.h>

/* @brief Static window class.
*/
class Window
{
private:
	static SDL_Window* s_nativeWin;
public:
	/* @brief Initializes static window instance.
	* Should be called once at the start.
	*/
	static void Init(const char* name, int width, int height);

	/* @brief Destroys window and cleanup.
	* Should be called at the end.
	*/
	static void Destroy();

	static SDL_Window* GetNativeWindow();

	static int GetWidth();
	static int GetHeight();
	static float GetAspectRatio();
};