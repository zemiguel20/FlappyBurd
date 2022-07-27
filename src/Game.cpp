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

static bool running = false;
static Renderer* renderer = nullptr;
static float DELTA_TIME = 0.0f;
static std::vector<GameObject*>* sceneObjects = nullptr;
static std::vector<Sprite*>* sprites = nullptr;
static Camera* cam = nullptr;
static bool space_pressed = false;

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
}

Game::~Game()
{
	delete renderer;
	Window::Destroy();
	SDL_Quit();
}

// Initialize game variables
static void Start()
{
	//Load sprites
	sprites = new std::vector<Sprite*>;
	sprites->push_back(new Sprite("res/burd.png", renderer->GetRenderContext()));
	sprites->push_back(new Sprite("res/background-day.png", renderer->GetRenderContext()));
	sprites->push_back(new Sprite("res/dirtsprite.png", renderer->GetRenderContext()));

	//Load game objects
	sceneObjects = new std::vector<GameObject*>;
	sceneObjects->push_back(new GameObject(vec2(0.0f, 0.0f), 0.0f, 3.0f, (*sprites)[0], 3)); //Bird
	sceneObjects->push_back(new GameObject(vec2(0.0f, 0.0f), 0.0f, 1.0f, (*sprites)[1], 0)); //Background
	sceneObjects->push_back(new GameObject(vec2(0.0f, -450.0f), 0.0f, 3.0f, (*sprites)[2], 1)); //Ground

	cam = new Camera;

	DELTA_TIME = 0.0f;
}

static void Update()
{
	cam->UpdateViewportTransform();

	GameObject* bird = (*sceneObjects)[0];
	if (space_pressed)
	{
		bird->velocity = vec2(0, 500);
		space_pressed = false;
	}
	bird->velocity += vec2(0, -1200) * DELTA_TIME;

	bird->transform.position += bird->velocity * DELTA_TIME;
	//std::cout << bird.transform.position << std::endl;

	bird->transform.rotation = bird->transform.rotation >= 360.0f ? 0 : (bird->transform.rotation + 360.0f * DELTA_TIME);

}

// Destroy game variables
static void Destroy()
{
	delete cam;

	for (Sprite* sprite : *sprites)
		delete sprite;
	delete sprites;

	for (GameObject* obj : *sceneObjects)
		delete obj;
	delete sceneObjects;
}

static void Render()
{
	for (GameObject* obj : *sceneObjects)
	{
		renderer->EnqueueSprite(obj->sprite, obj->transform, obj->zind);
	}
	renderer->Render(*cam);
}

static void ProcessEventQueue()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		//If Escape pressed, close window
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)
				running = false;
			else if (event.key.keysym.sym == SDLK_SPACE)
				space_pressed = true;
		}
		//If Window closed using window menu
		else if (event.type == SDL_WINDOWEVENT)
		{
			if (event.window.event == SDL_WINDOWEVENT_CLOSE)
				running = false;
		}
	}
}

void Game::Run()
{
	running = true;

	Start();

	auto start = std::chrono::high_resolution_clock::now();
	while (running)
	{
		//DELTA TIME UPDATE
		SDL_Delay(1); //Guarantees non zero
		auto end = std::chrono::high_resolution_clock::now();
		auto a = end - start;
		DELTA_TIME = std::chrono::duration<float>(end - start).count();
		start = end;

		ProcessEventQueue();

		Update();

		Render();
	}

	Destroy();
}
