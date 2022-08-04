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
static bool game_over = false;

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

	GameObject* bird = new GameObject();
	bird->transform = Transform(vec2(0.0f, 0.0f), 0.0f, 3.0f);
	bird->sprite = (*sprites)[0];
	bird->zind = 3;
	bird->boxColliderSize = vec2(22.0f, 13.0f);
	sceneObjects->push_back(bird);

	GameObject* background = new GameObject();
	background->transform = Transform(vec2(0.0f, 0.0f), 0.0f, 1.0f);
	background->sprite = (*sprites)[1];
	sceneObjects->push_back(background);

	//Test ground
	GameObject* ground = new GameObject();
	ground->transform = Transform(vec2(0.0f, -450.0f), 0.0f, 3.0f);
	ground->sprite = (*sprites)[2];
	ground->zind = 1;
	ground->boxColliderSize.x = (float)ground->sprite->GetWidth();
	ground->boxColliderSize.y = (float)ground->sprite->GetHeight();
	sceneObjects->push_back(ground);

	//Test invisible object
	sceneObjects->push_back(new GameObject());

	cam = new Camera;

	DELTA_TIME = 0.0f;
}

static void Update()
{
	cam->UpdateViewportTransform();

	GameObject* bird = (*sceneObjects)[0];


	if (game_over == false)
	{
		/*********************
		* BIRD MOVEMENT
		*********************/

		if (space_pressed)
		{
			bird->velocity = vec2(0, 500);
			space_pressed = false;
		}
		bird->velocity += vec2(0, -1200) * DELTA_TIME;
		bird->transform.position += bird->velocity * DELTA_TIME;

		bird->transform.rotation = bird->transform.rotation >= 360.0f ? 0 : (bird->transform.rotation + 360.0f * DELTA_TIME);

		//Keep bird within screen limits
		float limit = 490.0f;
		if (bird->transform.position.y > limit)
		{
			bird->transform.position.y = limit;
			bird->velocity = vec2();
		}
		else if (bird->transform.position.y < -limit)
		{
			bird->transform.position.y = -limit;
			bird->velocity = vec2();
		}


		/****************
		* CHECK COLLISIONS
		*****************/

		//Bird bounding box
		float xLeft_bird = bird->transform.position.x - (bird->boxColliderSize.x * 0.5f * bird->transform.scale);
		float xRight_Bird = bird->transform.position.x + (bird->boxColliderSize.x * 0.5f * bird->transform.scale);
		float yTop_bird = bird->transform.position.y + (bird->boxColliderSize.y * 0.5f * bird->transform.scale);
		float yBot_bird = bird->transform.position.y - (bird->boxColliderSize.y * 0.5f * bird->transform.scale);

		//Ground
		GameObject* ground = (*sceneObjects)[2];
		float xLeft_ground = ground->transform.position.x - (ground->boxColliderSize.x * 0.5f * ground->transform.scale);
		float xRight_ground = ground->transform.position.x + (ground->boxColliderSize.x * 0.5f * ground->transform.scale);
		float yTop_ground = ground->transform.position.y + (ground->boxColliderSize.y * 0.5f * ground->transform.scale);
		float yBot_ground = ground->transform.position.y - (ground->boxColliderSize.y * 0.5f * ground->transform.scale);

		if (xLeft_bird >= xLeft_ground && xLeft_bird <= xRight_ground && yTop_bird >= yBot_ground && yTop_bird <= yTop_ground //Top left
			|| xRight_Bird >= xLeft_ground && xRight_Bird <= xRight_ground && yTop_bird >= yBot_ground && yTop_bird <= yTop_ground //Top right
			|| xRight_Bird >= xLeft_ground && xRight_Bird <= xRight_ground && yBot_bird >= yBot_ground && yBot_bird <= yTop_ground //Bot right
			|| xLeft_bird >= xLeft_ground && xLeft_bird <= xRight_ground && yBot_bird >= yBot_ground && yBot_bird <= yTop_ground) //Bot left
		{
			game_over = true;
			std::cout << "GAME OVER" << std::endl;
		}
	}
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
		if (obj->sprite != nullptr)
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
