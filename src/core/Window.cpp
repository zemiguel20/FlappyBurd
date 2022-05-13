#include "Window.h"

#include <iostream>
#include <sstream>

#include <SDL.h>

Window* Window::instance = nullptr;

void Window::Init(const char* name, int width, int height)
{
	if (instance != nullptr)
	{
		std::cout << "Window already initialized. Action skipped." << std::endl;
		return;
	}

	instance = new Window;

	instance->nativeWin = SDL_CreateWindow(name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);
	if (instance->nativeWin == nullptr)
	{
		std::stringstream msg;
		msg << "ERROR: Failed to create window: " << SDL_GetError();
		throw msg.str();
	}
}

void Window::Destroy()
{
	SDL_DestroyWindow(instance->nativeWin);
	delete instance;
}

SDL_Window* Window::GetNativeWindow()
{
	return instance->nativeWin;
}
