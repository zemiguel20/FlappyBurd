#include "Game.h"

#include <SDL.h>
#include "ResourceLoader.h"

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

	m_window.Init("FlappyBurd", SCREEN_WIDTH, SCREEN_HEIGHT);

	m_renderer.Init(m_window);

	m_running = true;
}

Game::~Game()
{
	SDL_Quit();
}

void Game::Run()
{
	//Load bird sprite
	Sprite birdSprite = ResourceLoader::LoadSprite(m_renderer, "res/burd.png");

	//Load background
	Sprite bgSprite = ResourceLoader::LoadSprite(m_renderer, "res/background-day.png");

	//Game loop
	while (m_running)
	{
		ProcessEventQueue();

		m_renderer.ClearBuffer();

		//Draw background
		m_renderer.RenderSprite(bgSprite, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.45);
		//Draw bird in center
		m_renderer.RenderSprite(birdSprite, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 2);

		m_renderer.SwapBuffers();
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
