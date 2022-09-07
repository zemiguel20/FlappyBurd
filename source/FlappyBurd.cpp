#include "FlappyBurd.h"

Core::App *Core::CreateApp()
{
    return new FlappyBurd();
}

void FlappyBurd::Start()
{
    Log::Info("Loading FlappyBurd...");
    // Setup window
    // TODO: Query display to determine resolution
    SetWindowSize(Config::REF_SCREEN_W, Config::REF_SCREEN_H);
    SetWindowTitle("FlappyBurd");

    player = new Bird();
    cam = new Camera2D();
    bg = new Background();
    sgrnd = new ScrollingGround();

    Log::Info("FlappyBurd loaded");
}

void FlappyBurd::Update()
{
    player->Update();
    sgrnd->Update();
}

void FlappyBurd::Render()
{
    bg->Render(*cam);
    sgrnd->Render(*cam);
    player->Render(*cam);
}

void FlappyBurd::Close()
{
    Log::Info("Unloading FlappyBurd...");
    delete bg;
    delete player;
    delete cam;
    Log::Info("FlappyBurd unloaded");
}