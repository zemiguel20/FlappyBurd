#include "Game.h"

#include <raylib.h>
#include <vector>
#include <string>

#define SCREEN_WIDTH   360 // Reference screen width
#define SCREEN_HEIGHT  640 // Reference screen height

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
// GAME VARIABLES
//-----------------------------------------------------------------------------

typedef struct Bird {
	Vector2 position;
	float rotation;
	float scale;
	Texture2D* texture;
	Vector2 velocity;
	Rectangle collider;
} Bird;

typedef struct Background
{
	Texture2D* texture;
} Background;

typedef struct GroundBlock
{
	Vector2 position;
	float scale;
	Texture2D* texture;
	Rectangle collider;
} GroundBlock;

float SCROLL_VEL = 70.0f;

static Bird player;
static Background bg;
static std::vector<GroundBlock> blocks;
static std::vector<Texture2D> textures;
static Camera2D camera;
static bool isGameOver = false;

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// GAME RUNTIME
//-----------------------------------------------------------------------------

// Different stages of runtime
static void Start();
static void UpdateBirdMovement();
static void UpdateScrolling();
static void ResolveCollisions();
static void Render();
static void Destroy();

void Game::Run()
{
	Start();

	while (!WindowShouldClose())
	{
		if (!isGameOver)
		{
			UpdateBirdMovement();
			UpdateScrolling();
			ResolveCollisions();
		}

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

	// Init player
	player.position = Vector2(0.0f, 0.0f);
	player.rotation = 0.0f;
	player.scale = 2.0f;
	player.texture = &textures[0];
	player.velocity = Vector2(0.0f, 0.0f);
	player.collider = Rectangle(-11.0f, 6.5f, 22.0f, 13.0f);

	// Init background
	bg.texture = &textures[1];

	// Init ground blocks
	GroundBlock gbBase;
	gbBase.scale = 2.0f;
	gbBase.texture = &textures[2];
	gbBase.position.x = (-SCREEN_WIDTH / 2) + (gbBase.texture->width * gbBase.scale / 2);
	gbBase.position.y = -300.0f;
	gbBase.collider.width = (float)gbBase.texture->width;
	gbBase.collider.height = (float)gbBase.texture->height;
	gbBase.collider.x = -(float)gbBase.texture->width / 2;
	gbBase.collider.y = (float)gbBase.texture->height / 2;
	blocks = { gbBase, gbBase, gbBase, gbBase, gbBase };
	for (int i = 0; i < blocks.size(); i++)
	{
		blocks[i].position.x += blocks[i].texture->width * blocks[i].scale * i;
	}
}

void UpdateBirdMovement()
{
	// Jump
	if (IsKeyPressed(KEY_SPACE))
	{
		player.velocity.y = 500.0f;
	}

	// Acceleration
	player.velocity.y += -1200.0f * GetFrameTime();
	// Apply velocity to position
	player.position.y += player.velocity.y * GetFrameTime();
	// Rotation (value kept between 0-360)
	player.rotation += 360.0f * GetFrameTime();
	if (player.rotation >= 360.0f)
		player.rotation -= 360.0f;

	//Keep bird within screen limits
	float limit = (float)SCREEN_HEIGHT / 2 - (float)player.texture->height / 2;
	if (player.position.y > limit)
	{
		player.position.y = limit;
		player.velocity.y = 0.0f;
	}
	else if (player.position.y < -limit)
	{
		player.position.y = -limit;
		player.velocity.y = 0.0f;
	}
}

void UpdateScrolling()
{
	for (GroundBlock& gb : blocks)
	{
		gb.position.x -= SCROLL_VEL * GetFrameTime();
	}
	bool firstBlockNotVisible = (blocks[0].position.x + (blocks[0].texture->width / 2) * blocks[0].scale) < -(SCREEN_WIDTH / 2);
	if (firstBlockNotVisible)
	{
		GroundBlock block = blocks[0];
		block.position.x = blocks.back().position.x + block.texture->width * block.scale;
		blocks.erase(blocks.begin());
		blocks.push_back(block);
	}
}

// Scale Local collider and translate to World
static Rectangle GetTransformedCollider(Rectangle collider, Vector2 pos, float scale)
{
	// Scale collider
	collider.width *= scale;
	collider.height *= scale;
	collider.x *= scale;
	collider.y *= scale;
	// Local to World Space
	collider.x += pos.x;
	collider.y += pos.y;

	return collider;
}

void ResolveCollisions()
{
	Rectangle birdCollider = GetTransformedCollider(player.collider, player.position, player.scale);
	birdCollider.y *= -1.0f; // raylib uses downwards Y

	// Check collisions with ground
	for (GroundBlock& gb : blocks)
	{
		Rectangle groundCollider = GetTransformedCollider(gb.collider, gb.position, gb.scale);
		groundCollider.y *= -1.0f; // raylib uses downwards Y
		if (CheckCollisionRecs(birdCollider, groundCollider))
		{
			isGameOver = true;
			break;
		}
	}
}

// Draws texture at center pos, with certain scale and rotation over itself
static void DrawTexture(Texture2D tex, Vector2 pos, float scale, float rot)
{
	Rectangle source(
		0.0f,
		0.0f,
		(float)tex.width,
		(float)tex.height
	);
	Rectangle dest(
		pos.x,
		-pos.y, //Screen Y axis is downwards
		source.width * scale,
		source.height * scale
	);
	Vector2 origin(
		dest.width * 0.5f,
		dest.height * 0.5f
	);
	DrawTexturePro(tex, source, dest, origin, rot, WHITE);
}

void Render()
{
	BeginDrawing();

	ClearBackground(RAYWHITE);

	BeginMode2D(camera);

	// Draw background
	DrawTexture(*bg.texture, Vector2(0.0f, 0.0f), 0.6f, 0.0f);

	// Draw ground blocks
	for (GroundBlock& gb : blocks)
	{
		DrawTexture(*gb.texture, gb.position, gb.scale, 0.0f);
	}

	// Draw bird
	DrawTexture(*player.texture, player.position, player.scale, player.rotation);

	//Debug lines camera center
	DrawLine((int)camera.target.x, -SCREEN_HEIGHT * 10, (int)camera.target.x, SCREEN_HEIGHT * 10, GREEN);
	DrawLine(-SCREEN_WIDTH * 10, (int)camera.target.y, SCREEN_WIDTH * 10, (int)camera.target.y, GREEN);

	if (isGameOver)
	{
		DrawText("GAME OVER", 0, 0, 20, RED);
	}

	Rectangle birdCollider = GetTransformedCollider(player.collider, player.position, player.scale);
	DrawRectangle((int)birdCollider.x, (int)-birdCollider.y, (int)birdCollider.width, (int)birdCollider.height, PURPLE);


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