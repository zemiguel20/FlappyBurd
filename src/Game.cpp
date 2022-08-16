#include "Game.h"

#include <raylib.h>
#include <vector>
#include <algorithm>
#include <string>
#include "GameObject.h"

#define SCREEN_WIDTH   360
#define SCREEN_HEIGHT  640

//-----------------------------------------------------------------------------
// CORE LOADING/UNLOADING
//-----------------------------------------------------------------------------

bool Game::Init()
{
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "FlappyBurd");
	if (!IsWindowReady())
		return false;

	//SetTargetFPS(60);

	return true;
}

void Game::Close()
{
	CloseWindow();
}

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// GAME RUNTIME
//-----------------------------------------------------------------------------

// Different stages of runtime
static void Start();	// Initialize game variables
static void Update();	// Update game state for current frame
static void Render();	// Display current frame
static void Destroy();	// Unload game variables

// Global Variables
static std::vector<Texture2D> textures;
static Camera2D camera;
static std::vector<GameObject> sceneObjects;
static bool isGameOver = false;

void Game::Run()
{
	Start();

	bool resbool = false;
	while (!WindowShouldClose())
	{
		//	ProcessEventQueue();
		Update();

		Render();
	}

	Destroy();
}

void Start()
{
	//Load Textures
	textures.push_back(LoadTexture("res/burd.png"));
	textures.push_back(LoadTexture("res/background-day.png"));
	textures.push_back(LoadTexture("res/dirtsprite.png"));

	// Init camera
	camera.offset.x = (float)GetScreenWidth() / 2;
	camera.offset.y = (float)GetScreenHeight() / 2;
	camera.target.x = 0.0f;
	camera.target.y = 0.0f;
	camera.rotation = 0.0f;
	camera.zoom = 1.0f;

	GameObject bird;
	bird.scale = 2.0f;
	bird.texture = &textures[0];
	bird.zind = 3;
	bird.boxColliderSize = Vector2(22.0f, 13.0f);
	sceneObjects.push_back(bird);

	GameObject background;
	background.texture = &textures[1];
	background.scale = 0.65f;
	sceneObjects.push_back(background);

	//Test ground
	GameObject ground;
	ground.position.y = -300.0f;
	ground.scale = 2.0f;
	ground.texture = &textures[2];
	ground.zind = 1;
	ground.boxColliderSize.x = (float)ground.texture->width;
	ground.boxColliderSize.y = (float)ground.texture->height;
	sceneObjects.push_back(ground);

	//Test invisible object
	sceneObjects.push_back(GameObject());
}

void Update()
{
	if (!isGameOver)
	{
		/*********************
		* BIRD MOVEMENT
		*********************/

		GameObject* bird = &sceneObjects[0];

		// Jump
		if (IsKeyPressed(KEY_SPACE))
		{
			bird->velocity.y = 500.0f;
		}

		// Acceleration
		bird->velocity.y += -1200.0f * GetFrameTime();
		// Apply velocity to position
		bird->position.y += bird->velocity.y * GetFrameTime();
		// Rotation (value kept between 0-360)
		bird->rotation += 360.0f * GetFrameTime();
		if (bird->rotation >= 360.0f)
			bird->rotation -= 360.0f;

		//Keep bird within screen limits
		float limit = 300;
		if (bird->position.y > limit)
		{
			bird->position.y = limit;
			bird->velocity.y = 0.0f;
		}
		else if (bird->position.y < -limit)
		{
			bird->position.y = -limit;
			bird->velocity.y = 0.0f;
		}

		/****************
		* CHECK COLLISIONS
		*****************/

		//Bird bounding box
		float xLeft_bird = bird->position.x - (bird->boxColliderSize.x * 0.5f * bird->scale);
		float xRight_Bird = bird->position.x + (bird->boxColliderSize.x * 0.5f * bird->scale);
		float yTop_bird = bird->position.y + (bird->boxColliderSize.y * 0.5f * bird->scale);
		float yBot_bird = bird->position.y - (bird->boxColliderSize.y * 0.5f * bird->scale);

		//Ground
		GameObject* ground = &sceneObjects[2];
		float xLeft_ground = ground->position.x - (ground->boxColliderSize.x * 0.5f * ground->scale);
		float xRight_ground = ground->position.x + (ground->boxColliderSize.x * 0.5f * ground->scale);
		float yTop_ground = ground->position.y + (ground->boxColliderSize.y * 0.5f * ground->scale);
		float yBot_ground = ground->position.y - (ground->boxColliderSize.y * 0.5f * ground->scale);

		if (xLeft_bird >= xLeft_ground && xLeft_bird <= xRight_ground && yTop_bird >= yBot_ground && yTop_bird <= yTop_ground //Top left
			|| xRight_Bird >= xLeft_ground && xRight_Bird <= xRight_ground && yTop_bird >= yBot_ground && yTop_bird <= yTop_ground //Top right
			|| xRight_Bird >= xLeft_ground && xRight_Bird <= xRight_ground && yBot_bird >= yBot_ground && yBot_bird <= yTop_ground //Bot right
			|| xLeft_bird >= xLeft_ground && xLeft_bird <= xRight_ground && yBot_bird >= yBot_ground && yBot_bird <= yTop_ground) //Bot left
		{
			isGameOver = true;
		}
	}
}

// Render queue used to sort scene objects by z-index
static std::vector<GameObject> renderQueue;

void Render()
{
	// Enqueue scene objects and sort by z-index
	renderQueue.clear();
	for (GameObject& obj : sceneObjects)
		if (obj.texture)
			renderQueue.push_back(obj);
	std::sort(renderQueue.begin(), renderQueue.end(),
		[](GameObject& a, GameObject& b) {
			return a.zind < b.zind;
		});

	BeginDrawing();

	ClearBackground(RAYWHITE);

	BeginMode2D(camera);

	for (GameObject& obj : renderQueue)
	{
		Rectangle source;
		source.x = 0.0f;
		source.y = 0.0f;
		source.width = (float)obj.texture->width;
		source.height = (float)obj.texture->height;

		Rectangle dest;
		dest.x = obj.position.x;
		dest.y = -obj.position.y; //Screen Y axis is downwards, so invert
		dest.width = source.width * obj.scale;
		dest.height = source.height * obj.scale;

		Vector2 origin;
		origin.x = dest.width / 2;
		origin.y = dest.height / 2;

		DrawTexturePro(*obj.texture, source, dest, origin, obj.rotation, WHITE);
	}

	//Debug lines camera center
	DrawLine((int)camera.target.x, -SCREEN_HEIGHT * 10, (int)camera.target.x, SCREEN_HEIGHT * 10, GREEN);
	DrawLine(-SCREEN_WIDTH * 10, (int)camera.target.y, SCREEN_WIDTH * 10, (int)camera.target.y, GREEN);

	if (isGameOver)
	{
		DrawText("GAME OVER", 0, 0, 20, RED);
	}

	EndMode2D();

	// DEBUG TEXT
	DrawFPS(0, 0);

	EndDrawing();
}

void Destroy()
{
	//Unload Textures
	for (Texture2D& tex : textures)
		UnloadTexture(tex);
}