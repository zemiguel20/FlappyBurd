#include "FlappyBurd.h"
#include "Config.h"

Core::App *Core::CreateApp()
{
    return new FlappyBurd();
}

void FlappyBurd::Start()
{
    Log::Info("Loading FlappyBurd...");
    // Setup window
    SetWindowSize(Config::REF_SCREEN_W, Config::REF_SCREEN_H);
    SetWindowTitle("FlappyBurd");

    // Create camera
    cam = new Camera2D();

    // Create game objects
    player = new Bird();
    bg = new Background();
    ground = new ScrollingGround();
    barriers = new ScrollingBarriers();

    // Init score and highscore
    score = 0;
    LoadHighscore();

    // Load scoring sound
    scoreSound = new Sound("assets/sfx_coin.wav");

    // Set game state to START
    state = START;
    // Start game start cooldown timer
    startRunTimer = new Timer(1.0f);

    ui = new UI(state, *startRunTimer, score, highscore);

    Log::Info("FlappyBurd loaded");
}

void FlappyBurd::Close()
{
    Log::Info("Unloading FlappyBurd...");

    // Save highscore to file
    SaveHighscore();

    // Unload scoring sound
    delete scoreSound;

    // Unload game objects
    delete player;
    delete bg;
    delete ground;
    delete barriers;

    // Unload camera
    delete cam;

    // Delete timer
    delete startRunTimer;

    // Unload UI
    delete ui;

    Log::Info("FlappyBurd unloaded");
}

void FlappyBurd::Update()
{
    if (state == START || state == GAME_OVER)
    {
        if (!startRunTimer->Finished())
        {
            startRunTimer->Tick();
        }
        else if (Input::IsKeyPressed(Input::KEY_SPACE))
        {
            score = 0;
            barriers->Reset();
            player->Reset();
            state = RUNNING;
        }
    }

    if (state == RUNNING)
    {
        player->Move();
        ground->Scroll();
        barriers->Scroll();

        if (barriers->CheckGapPassed(*player))
        {
            score++;
            scoreSound->Play();
        }

        // Game Over on collision
        if (ground->CheckCollision(*player) ||
            barriers->CheckCollision(*player))
        {
            state = GAME_OVER;
            // Update highscore
            if (score > highscore)
            {
                highscore = score;
            }

            startRunTimer->Reset();
        }
    }
}

void FlappyBurd::Render()
{
    bg->Render(*cam);
    barriers->Render(*cam);
    ground->Render(*cam);
    player->Render(*cam);
    ui->Render();
}

void FlappyBurd::LoadHighscore()
{
    // TODO: implement
}

void FlappyBurd::SaveHighscore()
{
    // TODO: implement
}