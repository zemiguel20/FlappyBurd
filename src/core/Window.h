#pragma once

#include <SDL.h>

class Window
{
	/* Static window instance and interface */
private:
	static Window* instance;
public:
	static void Init(const char* name, int width, int height);
	static void Destroy();

	static SDL_Window* GetNativeWindow();

	/* Window properties */
private:
	SDL_Window* nativeWin = nullptr;
};