#include "Game.h"

#include <raylib.h>
#include <vector>
#include <string>
#include <sstream>
#include <charconv>

//#define VISUAL_DEBUG

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

typedef struct Barrier
{
	Vector2 position;
	float scale;
	Texture2D* texture;

	float topPos; // Y local position of the top part of the barrier
	float botPos; // Y local position of the bottom part of the barrier
	Rectangle obsCollider; // Collider dimensions for the obstacle part of the barrier
	Rectangle gapCollider; // Collider dimensions for the gap of the barrier
	bool passed; // If barrier was passed or not. Middle collider used for this.
} Barrier;

enum GameState
{
	START,
	RUNNING,
	GAME_OVER
};

const int SCREEN_WIDTH = 360; // Reference screen width
const int SCREEN_HEIGHT = 640; // Reference screen height

const float SCROLL_VEL = 70.0f; // Abs velocity of the scrolling ground and barriers

static GameState gameState;
static Bird player;
static Background bg;
static std::vector<GroundBlock> blocks;
static std::vector<Barrier> barriers;
static Camera2D camera;
static int score;
static int highscore;
static float gameOverCooldown;

static std::vector<Texture2D> textures; // Stores loaded textures
static Font font; // stores loaded font
static Sound jumpSound;
static Sound pointSound;

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// CORE LOADING/UNLOADING
//-----------------------------------------------------------------------------

static void LoadHighscore();
static void SaveHighscore();

bool Game::Init()
{
	SetConfigFlags(FLAG_VSYNC_HINT);
	// Init window and rendering
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "FlappyBurd");
	if (!IsWindowReady())
		return false;

	// Initialize audio
	InitAudioDevice();

	// Load Textures
	textures.push_back(LoadTexture("res/burd.png"));
	textures.push_back(LoadTexture("res/background-day.png"));
	textures.push_back(LoadTexture("res/dirtsprite.png"));
	textures.push_back(LoadTexture("res/log.png"));

	// Load Font
	font = LoadFont("res/04B_30__.TTF");

	// Load Sounds
	jumpSound = LoadSound("res/sfx_jump.mp3");
	pointSound = LoadSound("res/sfx_coin.wav");

	// Init camera
	camera.offset.x = (float)(SCREEN_WIDTH / 2);
	camera.offset.y = (float)(SCREEN_HEIGHT / 2);
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
	gbBase.texture = &textures[2];
	gbBase.scale = 2.0f;
	gbBase.position.x = 0.0f;
	gbBase.position.y = -300.0f;
	gbBase.collider.width = (float)gbBase.texture->width;
	gbBase.collider.height = (float)gbBase.texture->height;
	gbBase.collider.x = -(float)gbBase.texture->width / 2;
	gbBase.collider.y = (float)gbBase.texture->height / 2;

	blocks = { gbBase, gbBase, gbBase, gbBase, gbBase };

	// Init barriers
	Barrier brBase;
	brBase.texture = &textures[3];
	brBase.scale = 3.0f;
	brBase.position = Vector2(50.0f, 0.0f);
	brBase.passed = false;
	brBase.gapCollider.width = 5.0f;
	brBase.gapCollider.height = 50.0f;
	brBase.gapCollider.x = -(brBase.gapCollider.width / 2);
	brBase.gapCollider.y = brBase.gapCollider.height / 2;
	brBase.obsCollider.width = 18.0f;
	brBase.obsCollider.height = 244.0f;
	brBase.obsCollider.x = -(brBase.obsCollider.width / 2);
	brBase.obsCollider.y = brBase.obsCollider.height / 2;
	brBase.topPos = brBase.gapCollider.y + brBase.obsCollider.y;
	brBase.botPos = -brBase.topPos;

	barriers = { brBase, brBase, brBase };

	LoadHighscore();


	return true;
}

void Game::Close()
{
	SaveHighscore();

	// Unload Textures
	for (Texture2D& tex : textures)
		UnloadTexture(tex);

	// Unload font
	UnloadFont(font);

	// Unload sounds
	UnloadSound(jumpSound);
	UnloadSound(pointSound);

	CloseAudioDevice();

	// Unload window and render context
	CloseWindow();
}

void LoadHighscore()
{
	std::stringstream strm;
	strm << GetApplicationDirectory();
	strm << "highscore.txt";
	std::string path = strm.str();
	if (FileExists(path.c_str()))
	{
		char* text = LoadFileText(path.c_str());
		highscore = std::atoi(text);
		UnloadFileText(text);
	}
	else
	{
		highscore = 0;
	}
}

void SaveHighscore()
{
	std::stringstream strm;
	strm << GetApplicationDirectory();
	strm << "highscore.txt";
	std::string path = strm.str();
	char text[10];
	std::to_chars(text, text + 10, highscore);
	SaveFileText(path.c_str(), text);
}

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// GAME RUNTIME
//-----------------------------------------------------------------------------

// Different stages of runtime
static void ResetRun();
static void UpdateBirdMovement();
static void UpdateScrolling();
static void ResolveCollisions();
static void Render();

void Game::Run()
{
	gameState = START;
	ResetRun(); // Needed to initially position elements and set score to 0

	while (!WindowShouldClose())
	{
		if (gameState == START || gameState == GAME_OVER)
		{
			if (gameState == GAME_OVER && gameOverCooldown < 1.0f)
			{
				gameOverCooldown += GetFrameTime();
			}
			else if (IsKeyPressed(KEY_SPACE))
			{
				if (gameState == GAME_OVER && gameOverCooldown >= 1.0f)
				{
					ResetRun();
				}
				gameState = RUNNING;
			}
		}
		if (gameState == RUNNING)
		{
			UpdateBirdMovement();
			UpdateScrolling();
			ResolveCollisions();
		}

		Render();
	}
}

void ResetRun()
{
	// Player starting position
	player.position.y = 0.0f;

	// Set first block on leftmost side
	blocks[0].position.x =
		-(SCREEN_WIDTH / 2)
		+ ((blocks[0].texture->width / 2) * blocks[0].scale);
	// Set other blocks one after another
	for (int i = 1; i < blocks.size(); i++)
	{
		blocks[i].position.x =
			blocks[i - 1].position.x
			+ (blocks[i].texture->width * blocks[i].scale);
	}

	// Set first barrier at the right side outside of screen
	barriers[0].passed = false;
	barriers[0].position.x = SCREEN_WIDTH / 2;
	barriers[0].position.y = GetRandomValue(-150, 200);
	for (int i = 1; i < barriers.size(); i++)
	{
		barriers[i].position.x = barriers[i - 1].position.x + 250.0f;
		barriers[i].position.y = GetRandomValue(-150, 200);
		barriers[i].passed = false;
	}

	gameOverCooldown = 0.0f;

	score = 0;
}

void UpdateBirdMovement()
{
	// Jump
	if (IsKeyPressed(KEY_SPACE))
	{
		player.velocity.y = 500.0f;
		PlaySound(jumpSound);
	}

	// Acceleration
	player.velocity.y += -1200.0f * GetFrameTime();
	// Apply velocity to position
	player.position.y += player.velocity.y * GetFrameTime();
	// Rotation (value kept between 0-360)
	/*player.rotation += 360.0f * GetFrameTime();
	if (player.rotation >= 360.0f)
		player.rotation -= 360.0f;*/

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
	// GROUND
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

	// BARRIERS
	for (Barrier& br : barriers)
	{
		br.position.x -= SCROLL_VEL * GetFrameTime();
	}
	bool firstBarrierNotVisible = (barriers[0].position.x + (barriers[0].texture->width / 2) * barriers[0].scale) < -(SCREEN_WIDTH / 2);
	if (firstBarrierNotVisible)
	{
		Barrier barrier = barriers[0];
		barrier.position.x = barriers.back().position.x + 250.0f;
		barrier.position.y = GetRandomValue(-150, 200);
		barrier.passed = false;
		barriers.erase(barriers.begin());
		barriers.push_back(barrier);
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
			gameState = GAME_OVER;
			break;
		}
	}

	// Check with barriers
	for (Barrier& br : barriers)
	{
		if (!br.passed) {
			Rectangle gapCol = GetTransformedCollider(br.gapCollider, br.position, br.scale);
			gapCol.y *= -1.0f;
			if (CheckCollisionRecs(birdCollider, gapCol))
			{
				score++;
				if (score > highscore)
					highscore = score;

				br.passed = true;

				PlaySound(pointSound);

				break;
			}
		}

		Rectangle topCol = br.obsCollider;
		topCol.y += br.topPos;
		topCol = GetTransformedCollider(topCol, br.position, br.scale);
		topCol.y *= -1.0f;
		if (CheckCollisionRecs(birdCollider, topCol))
		{
			gameState = GAME_OVER;
			break;
		}

		Rectangle botCol = br.obsCollider;
		botCol.y += br.botPos;
		botCol = GetTransformedCollider(botCol, br.position, br.scale);
		botCol.y *= -1.0f;
		if (CheckCollisionRecs(birdCollider, botCol))
		{
			gameState = GAME_OVER;
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

// For debug collider
static void DrawCollider(Rectangle collider, Vector2 pos, float scale)
{
	collider.x *= scale;
	collider.y *= scale;
	collider.width *= scale;
	collider.height *= scale;

	collider.x += pos.x;
	collider.y += pos.y;

	collider.y *= -1.0f;

	DrawRectangleLinesEx(collider, 2.0f, PURPLE);
}

typedef struct Text
{
	std::string text;
	Font* font;
	int textSize;
	float spacing;
	Color color;
}Text;

static void DrawTextCentered(Text txt, int offsetY)
{
	Vector2 position;
	position.x = (SCREEN_WIDTH / 2);
	position.y = (SCREEN_HEIGHT / 2) - offsetY;
	Vector2 origin = MeasureTextEx(*txt.font, txt.text.c_str(), txt.textSize, txt.spacing);
	origin.x *= 0.5f;
	origin.y *= 0.5f;
	DrawTextPro(*txt.font, txt.text.c_str(), position, origin, 0.0f, txt.textSize, txt.spacing, txt.color);
}

void Render()
{
	BeginDrawing();

	ClearBackground(RAYWHITE);

	BeginMode2D(camera);

	// Draw background
	DrawTexture(*bg.texture, Vector2(0.0f, 0.0f), 0.6f, 0.0f);

	// Draw barriers
	for (Barrier& br : barriers)
	{
		// Draw upper part
		Vector2 posUpper = br.position;
		posUpper.y += br.topPos * br.scale;
		DrawTexture(*br.texture, posUpper, br.scale, 0.0f);

		// Draw bottom part
		Vector2 posBot = br.position;
		posBot.y += br.botPos * br.scale;
		DrawTexture(*br.texture, posBot, br.scale, 0.0f);
	}

	// Draw ground blocks
	for (GroundBlock& gb : blocks)
	{
		DrawTexture(*gb.texture, gb.position, gb.scale, 0.0f);
	}

	// Draw bird
	DrawTexture(*player.texture, player.position, player.scale, player.rotation);

	EndMode2D();

	Text txt;
	txt.text = "default";
	txt.font = &font;
	txt.textSize = 20;
	txt.spacing = 0.0f;
	txt.color = WHITE;

	// Draw Score
	if (gameState == RUNNING)
	{
		Text txtScore = txt;
		txtScore.text = std::to_string(score);
		txtScore.textSize = 30;
		DrawTextCentered(txtScore, 250);
	}

	// Draw End game panel
	if (gameState == GAME_OVER)
	{
		Text txtGameOver = txt;
		txtGameOver.text = "GAME OVER";
		txtGameOver.textSize = 40;
		txtGameOver.color = RED;
		DrawTextCentered(txtGameOver, 150);

		int posX = (SCREEN_WIDTH / 2) - 100;
		int posY = (SCREEN_HEIGHT / 2) - 100;
		DrawRectangle(posX, posY, 200, 200, BROWN);

		Text txtLabel = txt;
		txtLabel.text = "SCORE";
		DrawTextCentered(txtLabel, 60);

		Text txtNumber = txt;
		txtNumber.color = YELLOW;
		txtNumber.text = std::to_string(score);
		DrawTextCentered(txtNumber, 30);

		txtLabel.text = "HIGHSCORE";
		DrawTextCentered(txtLabel, -30);

		txtNumber.text = std::to_string(highscore);
		DrawTextCentered(txtNumber, -60);

		if (gameOverCooldown > 1.0f)
		{
			txtLabel.text = "Press SPACE to play";
			DrawTextCentered(txtLabel, -200);
		}
	}

	if (gameState == START)
	{
		Text txtTitle = txt;
		txtTitle.color = RED;
		txtTitle.textSize = 50;
		txtTitle.text = "FLAPPY";
		DrawTextCentered(txtTitle, 200);
		txtTitle.text = "BURD";
		DrawTextCentered(txtTitle, 150);

		Text txtLabel = txt;
		txtLabel.text = "Press SPACE to play";
		DrawTextCentered(txtLabel, -200);
	}

#ifdef VISUAL_DEBUG

	BeginMode2D(camera);

	//Debug lines camera center
	DrawLine((int)camera.target.x, -SCREEN_HEIGHT * 10, (int)camera.target.x, SCREEN_HEIGHT * 10, GREEN);
	DrawLine(-SCREEN_WIDTH * 10, (int)camera.target.y, SCREEN_WIDTH * 10, (int)camera.target.y, GREEN);

	DrawLine(-GetScreenWidth() * 10, -200, GetScreenWidth(), -200, WHITE);
	DrawLine(-GetScreenWidth() * 10, 150, GetScreenWidth(), 150, WHITE);

	// Draw colliders
	DrawCollider(player.collider, player.position, player.scale);
	for (GroundBlock& gb : blocks)
	{
		DrawCollider(gb.collider, gb.position, gb.scale);
	}
	for (Barrier& br : barriers)
	{
		DrawCollider(br.gapCollider, br.position, br.scale);
		Vector2 obsTopPos = br.position;
		obsTopPos.y += br.topPos * br.scale;
		DrawCollider(br.obsCollider, obsTopPos, br.scale);
		Vector2 obsBotPos = br.position;
		obsBotPos.y += br.botPos * br.scale;
		DrawCollider(br.obsCollider, obsBotPos, br.scale);
	}

	EndMode2D();

	DrawFPS(0, 0);
#endif // VISUAL_DEBUG


	EndDrawing();
}