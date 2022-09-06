#include "Core.h"

#include <raylib.h>

//------------------------------------------------------------------------------
// ENTRY POINT
//------------------------------------------------------------------------------
int main()
{
    Core::App *app = Core::CreateApp();

    if (app->Init())
    {
        app->Start();
        while (!::WindowShouldClose())
        {
            app->PrepareFrame();
            app->Update();
            app->Render();
            app->FinishFrame();
        }
        app->Close();
    }

    app->Shutdown();
    delete app;

    return 0;
}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// APP BASE CLASS
//------------------------------------------------------------------------------
bool Core::App::Init()
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

void Core::App::Shutdown()
{
    ::CloseAudioDevice();
    ::CloseWindow();
}

void Core::App::PrepareFrame()
{
    // Set up a white canvas buffer
    BeginDrawing();
    ClearBackground(RAYWHITE);
}

void Core::App::FinishFrame()
{
    // End frame drawing and poll input
    EndDrawing();
}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// WINDOW MANAGEMENT FUNCTIONS
//------------------------------------------------------------------------------
void Core::SetWindowSize(int width, int height)
{
    ::SetWindowSize(width, height);
}
void Core::SetWindowTitle(const char *title)
{
    ::SetWindowTitle(title);
}
//------------------------------------------------------------------------------