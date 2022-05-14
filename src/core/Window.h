#pragma once

#include <SDL.h>

/* @brief Static window class.
* Manage static window instance.
*/
class Window
{
private:
	static Window* instance;
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

	/* Window properties */
private:
	SDL_Window* nativeWin = nullptr;
};