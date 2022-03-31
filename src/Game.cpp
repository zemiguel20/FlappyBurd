#include "Game.h"

#include <iostream>

#include "Sprite.h"

#define SCREEN_WIDTH   256
#define SCREEN_HEIGHT  455

Game::Game()
{
	// Initialize SDL sub-processes
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
		throw;
	}

	//Init Window
	m_window.Init("FlappyBurd", SCREEN_WIDTH, SCREEN_HEIGHT);

	//Initialize 2D renderer
	m_renderer = SDL_CreateRenderer(m_window.GetNativeWindow(), -1, SDL_RENDERER_ACCELERATED);
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

	SDL_Quit();
}

void Game::Run()
{
	//Load bird sprite
	Sprite birdSprite(m_renderer, "res/burd.png");

	//Load background
	Sprite bgSprite(m_renderer, "res/background-day.png");

	//Game loop
	while (m_running)
	{
		ProcessEventQueue();

		//Clear buffer
		SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
		SDL_RenderClear(m_renderer);

		SDL_Rect texrect;
		//Draw background
		texrect.x = 0;
		texrect.y = 0;
		texrect.w = bgSprite.GetWidth() * 0.5;
		texrect.h = bgSprite.GetHeight() * 0.5;
		SDL_RenderCopy(m_renderer, bgSprite.GetTexture(), NULL, &texrect);

		//Draw bird in center
		texrect.x = (m_window.GetWidth() - birdSprite.GetWidth()) / 2;
		texrect.y = (m_window.GetHeight() - birdSprite.GetHeight()) / 2;
		texrect.w = birdSprite.GetWidth();
		texrect.h = birdSprite.GetHeight();
		SDL_RenderCopy(m_renderer, birdSprite.GetTexture(), NULL, &texrect);

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
