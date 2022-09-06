#include "Core.h"

#include <raylib.h>

//------------------------------------------------------------------------------
// ENTRY POINT
//------------------------------------------------------------------------------
int main()
{
    CreateApp().Run();
    return 0;
}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// APP BASE CLASS
//------------------------------------------------------------------------------
bool App::AppInit()
{
    ::SetConfigFlags(FLAG_VSYNC_HINT);
    // Init window and rendering
    ::InitWindow(winW, winH, winName);
    if (!::IsWindowReady())
        return false;

    // Initialize audio
    ::InitAudioDevice();

    return true;
}

void App::AppClose()
{
    ::CloseAudioDevice();
    ::CloseWindow();
}

bool App::WindowShouldClose()
{
    return ::WindowShouldClose();
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