#include "FlappyBurd.h"

Core::App *Core::CreateApp()
{
    return new FlappyBurd();
}

void FlappyBurd::Start()
{
    // Setup window
    // TODO: Query display to determine resolution
    SetWindowSize(Config::REF_SCREEN_W, Config::REF_SCREEN_H);
    SetWindowTitle("FlappyBurd");

    player = new Bird();
    cam = new Camera2D();
    bg = new Background();
    sgrnd = new ScrollingGround();
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
    delete bg;
    delete player;
    delete cam;
}