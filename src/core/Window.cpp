#include "Window.h"

#include <iostream>
#include <sstream>

#include <SDL.h>

SDL_Window* Window::s_nativeWin = nullptr;

void Window::Init(const char* name, int width, int height)
{
	// Skip if window already initialized
	if (s_nativeWin != nullptr)
	{
		std::cout
			<< "Window already initialized. Action skipped."
			<< std::endl;
		return;
	}

	// Initialize window
	s_nativeWin = SDL_CreateWindow(
		name,
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		width,
		height,
		0
	);

	// If error initializing window, throw error
	if (s_nativeWin == nullptr)
	{
		std::stringstream msg;
		msg << "ERROR: Failed to create window: " << SDL_GetError();
		throw msg.str();
	}
}

void Window::Destroy()
{
	SDL_DestroyWindow(s_nativeWin);
}

SDL_Window* Window::GetNativeWindow()
{
	return s_nativeWin;
}
