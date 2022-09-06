#include "Core.h"

#include <raylib.h>

//------------------------------------------------------------------------------
// ENTRY POINT
//------------------------------------------------------------------------------
int main()
{
    App *app = CreateApp();

    if (app->Init())
    {
        app->Start(); // override
        while (!::WindowShouldClose())
        {
            app->PrepareFrame();
            app->Update(); // override
            app->FinishFrame();
        }
        app->Close(); // override
    }

    app->Shutdown();
    delete app;

    return 0;
}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// APP BASE CLASS
//------------------------------------------------------------------------------
bool App::Init()
{
    ::SetConfigFlags(FLAG_VSYNC_HINT);
    // Init window and rendering
    ::InitWindow(1240, 720, "Default");
    if (!::IsWindowReady())
        return false;

    // Initialize audio
    ::InitAudioDevice();

    return true;
}

void App::Shutdown()
{
    ::CloseAudioDevice();
    ::CloseWindow();
}

void App::PrepareFrame()
{
    // Set up a white canvas buffer
    BeginDrawing();
    ClearBackground(RAYWHITE);
}

void App::FinishFrame()
{
    // End frame drawing and poll input
    EndDrawing();
}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// WINDOW MANAGEMENT FUNCTIONS
//------------------------------------------------------------------------------
void Window::SetSize(int width, int height)
{
    ::SetWindowSize(width, height);
}
void Window::SetTitle(const char *title)
{
    ::SetWindowTitle(title);
}
//------------------------------------------------------------------------------