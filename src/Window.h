#pragma once

#include <SDL.h>

class Window
{
private:
	SDL_Window* m_nativeWindow = nullptr;

public:
	Window();
	~Window();

	void Init(const char* name, int width, int height);

	SDL_Window* GetNativeWindow();
	int GetWidth();
	int GetHeight();
};

