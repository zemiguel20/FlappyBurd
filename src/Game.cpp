#include "Game.h"

#include <SDL.h>
#include <iostream>

Game::Game(GameSettings set)
{
	//Store settings
	m_settings = set;

	// Initialize SDL sub-processes
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
		throw;
	}

	//Create Window
	m_window = SDL_CreateWindow(
		"FlappyBurd",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		m_settings.screenWidth, m_settings.screenHeight,
		0
	);
	if (m_window == nullptr)
	{
		std::cout << "Failed to create window: " << SDL_GetError() << std::endl;
		throw;
	}

	//Initialize 2D renderer
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
	if (m_renderer == nullptr)
	{
		std::cout << "Failed to initialize renderer: " << SDL_GetError() << std::endl;
		throw;
	}

	m_running = true;
}

Game::~Game()
{
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void Game::Run()
{
	//Game loop
	while (m_running)
	{
		ProcessEventQueue();

		//Clear buffer
		SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
		SDL_RenderClear(m_renderer);

		//Swap buffers
		SDL_RenderPresent(m_renderer);
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
