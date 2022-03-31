#include "Window.h"

#include <iostream>
#include <sstream>

Window::Window()
{
	m_nativeWindow = nullptr;
}

Window::~Window()
{
	SDL_DestroyWindow(m_nativeWindow);
}

void Window::Init(const char* name, int width, int height)
{
	m_nativeWindow = SDL_CreateWindow(name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);
	if (m_nativeWindow == nullptr)
	{
		std::stringstream msg;
		msg << "ERROR: Failed to create window: " << SDL_GetError();
		throw msg.str();
	}
}

SDL_Window* Window::GetNativeWindow()
{
	return m_nativeWindow;
}

int Window::GetWidth()
{
	int w;
	SDL_GetWindowSize(m_nativeWindow, &w, nullptr);
	return w;
}

int Window::GetHeight()
{
	int h;
	SDL_GetWindowSize(m_nativeWindow, nullptr, &h);
	return h;
}
