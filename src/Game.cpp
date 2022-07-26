#include "Game.h"

#include <SDL.h>
#include "core/Window.h"
#include "core/Renderer.h"
#include "core/Camera.h"
#include "core/GameObject.h"

#include <chrono>
#include <iostream>
#include <sstream>
#include <vector>

#define SCREEN_WIDTH   256
#define SCREEN_HEIGHT  455

static bool space_pressed = false;

static Renderer* renderer = nullptr;

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

	renderer = new Renderer(Window::GetNativeWindow());

	m_running = true;
}

Game::~Game()
{
	delete renderer;
	Window::Destroy();
	SDL_Quit();
}

void Game::Run()
{
	//Load sprites
	Sprite birdSprite("res/burd.png", renderer->GetRenderContext());
	Sprite bgSprite("res/background-day.png", renderer->GetRenderContext());

	//Load game objects
	std::vector<GameObject*> sceneObjects;
	GameObject bird(vec2(0.0f, 0.0f), 0.0f, 3.0f, &birdSprite, 1);
	sceneObjects.push_back(&bird);
	GameObject bg(vec2(0.0f, 0.0f), 0.0f, 1.0f, &bgSprite, 0);
	sceneObjects.push_back(&bg);

	//Create Camera
	Camera cam;

	// Delta time count init
	float DELTA_TIME = 0.0f; //Fraction of second
	auto start = std::chrono::high_resolution_clock::now();

	//Game loop
	while (m_running)
	{
		//DELTA TIME UPDATE
		SDL_Delay(1); //Guarantees non zero
		auto end = std::chrono::high_resolution_clock::now();
		auto a = end - start;
		DELTA_TIME = std::chrono::duration<float>(end - start).count();
		start = end;

		ProcessEventQueue();

		cam.UpdateViewportTransform();

		//Logic

		if (space_pressed)
		{
			bird.velocity = vec2(0, 500);
			space_pressed = false;
		}
		bird.velocity += vec2(0, -1200) * DELTA_TIME;

		bird.transform.position += bird.velocity * DELTA_TIME;
		//std::cout << bird.transform.position << std::endl;

		bird.transform.rotation = bird.transform.rotation >= 360.0f ? 0 : (bird.transform.rotation + 360.0f * DELTA_TIME);

		//Render
		for (GameObject* obj : sceneObjects)
		{
			renderer->EnqueueSprite(obj->sprite, obj->transform, obj->zind);
		}
		renderer->Render(cam);
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
				m_running = false;
			else if (event.key.keysym.sym == SDLK_SPACE)
				space_pressed = true;
		}
		//If Window closed using window menu
		else if (event.type == SDL_WINDOWEVENT)
		{
			if (event.window.event == SDL_WINDOWEVENT_CLOSE)
				m_running = false;
		}
	}
}
