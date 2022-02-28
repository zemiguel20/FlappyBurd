#include "Game.h"

#include <SDL.h>
#include <iostream>

Game::Game(GameSettings set)
{
	//Store settings
	settings = set;

	// Initialize SDL sub-processes
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
		throw;
	}

	//Create Window
	window = nullptr;
	window = SDL_CreateWindow("FlappyBurd",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		settings.screenWidth, settings.screenHeight,
		0);
	if (window == nullptr)
	{
		std::cout << "Failed to create window: " << SDL_GetError() << std::endl;
		throw;
	}

	running = true;
}

Game::~Game()
{
	SDL_DestroyWindow((SDL_Window*)window);
	SDL_Quit();
}

void Game::Run()
{
	//Game loop
	while (running)
	{
		//Process event queue
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			//If Escape pressed, close window
			if (event.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.sym == SDLK_ESCAPE)
				{
					running = false;
				}
			}
			//If Window closed using window menu
			else if (event.type == SDL_WINDOWEVENT)
			{
				if (event.window.event == SDL_WINDOWEVENT_CLOSE)
				{
					running = false;
				}
			}
		}

	}
}
