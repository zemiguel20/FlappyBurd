#include "FlappyBurd.h"

App *CreateApp()
{
    return new FlappyBurd();
}

void FlappyBurd::Start()
{
    // TODO: IMPLEMENT

    // Setup window
    // TODO: Query display to determine resolution
    Window::SetSize(360, 640);
    Window::SetTitle("FlappyBurd");

    player = new Bird();
    cam = new Camera2D();
}

void FlappyBurd::Update()
{
    player->Update();
}

void FlappyBurd::Render()
{
    player->Render(cam);
}

void FlappyBurd::Close()
{
    delete player;
    delete cam;
}