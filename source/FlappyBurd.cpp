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
}

void FlappyBurd::Update()
{
    player->Update();
}

void FlappyBurd::Render()
{
    player->Render(*cam);
}

void FlappyBurd::Close()
{
    delete player;
    delete cam;
}