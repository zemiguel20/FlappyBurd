#include "FlappyBurd.h"

App* CreateApp()
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
}

void FlappyBurd::Update()
{
    // TODO: IMPLEMENT
}

void FlappyBurd::Close()
{
    // TODO: IMPLEMENT
}