#include "FlappyBurd.h"

Core::App *Core::CreateApp()
{
    return new FlappyBurd();
}

void FlappyBurd::Start()
{
    // Setup window
    // TODO: Query display to determine resolution
    SetWindowSize(360, 640);
    SetWindowTitle("FlappyBurd");

    player = new Bird();
    cam = new Camera2D();
    bg = new Background();
}

void FlappyBurd::Update()
{
    player->Update();
}

void FlappyBurd::Render()
{
    bg->Render(*cam);
    player->Render(*cam);
}

void FlappyBurd::Close()
{
    delete bg;
    delete player;
    delete cam;
}