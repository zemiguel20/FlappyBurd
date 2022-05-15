#include "Game.h"

#include <SDL.h>
#include "core/Window.h"
#include "core/Renderer.h"
#include "core/ResourceLoader.h"

#include <iostream>
#include <sstream>

#define SCREEN_WIDTH   256
#define SCREEN_HEIGHT  455

Game::Game()
{
	// Initialize SDL sub-processes
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::stringstream msg;
		msg << "ERROR: Failed to initialize SDL: " << SDL_GetError();
		throw msg.str();
	}

	Window::Init("FlappyBurd", SCREEN_WIDTH, SCREEN_HEIGHT);

	Renderer::Init(Window::GetNativeWindow());

	ResourceLoader::Init(Renderer::GetRenderContext());

	m_running = true;
}

Game::~Game()
{
	ResourceLoader::Destroy();
	Renderer::Destroy();
	Window::Destroy();
	SDL_Quit();
}

void Game::Run()
{
	//Load bird sprite
	Sprite* birdSprite = ResourceLoader::LoadSprite("burd.png");

	//Load background
	Sprite* bgSprite = ResourceLoader::LoadSprite("background-day.png");

	//Game loop
	while (m_running)
	{
		ProcessEventQueue();

		Renderer::ClearBuffer();

		//Draw background
		Renderer::RenderSprite(bgSprite, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.45);
		//Draw bird in center
		Renderer::RenderSprite(birdSprite, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 2);

		Renderer::SwapBuffers();
	}
}

void Game::ProcessEventQueue()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		//If Escape pressed, close window
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				m_running = false;
			}
		}
		//If Window closed using window menu
		else if (event.type == SDL_WINDOWEVENT)
		{
			if (event.window.event == SDL_WINDOWEVENT_CLOSE)
			{
				m_running = false;
			}
		}
	}
}
