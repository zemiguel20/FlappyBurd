#include "Core.h"

#include <raylib.h>
#define RAYMATH_IMPLEMENTATION
#include <raymath.h>

//---------------------------------------------------------------
// ENTRY POINT
//---------------------------------------------------------------
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
//---------------------------------------------------------------

//---------------------------------------------------------------
// APP BASE CLASS
//---------------------------------------------------------------
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
//---------------------------------------------------------------

//---------------------------------------------------------------
// WINDOW MANAGEMENT FUNCTIONS
//---------------------------------------------------------------
void Core::SetWindowSize(int width, int height)
{
    ::SetWindowSize(width, height);
}
void Core::SetWindowTitle(const char *title)
{
    ::SetWindowTitle(title);
}
//---------------------------------------------------------------

//---------------------------------------------------------------
// ASSETS
//---------------------------------------------------------------
Core::Texture::Texture(const char *filepath)
{
    rl_texture = new ::Texture;
    *(::Texture *)rl_texture = ::LoadTexture(filepath);
}

Core::Texture::~Texture()
{
    ::UnloadTexture(*(::Texture *)rl_texture);
    delete (::Texture *)rl_texture;
}

int Core::Texture::Width() const
{
    return ((::Texture *)rl_texture)->width;
}

int Core::Texture::Height() const
{
    return ((::Texture *)rl_texture)->height;
}

void *Core::Texture::Data() const
{
    return rl_texture;
}
//---------------------------------------------------------------

//---------------------------------------------------------------
// RENDERING
//---------------------------------------------------------------
void Core::RenderSprite(
    const Core::Camera2D &cam,
    const Core::Transform2D &tf,
    const Core::Texture &tex)
{
    // NOTE: raylib uses downwards Y world axis

    // Create raylib camera object
    ::Camera2D rl_cam;
    rl_cam.offset.x = ::GetScreenWidth() / 2;
    rl_cam.offset.y = ::GetScreenHeight() / 2;
    rl_cam.target.x = cam.tf.position.x;
    rl_cam.target.y = -(cam.tf.position.y);
    rl_cam.rotation = cam.tf.rotation;
    rl_cam.zoom = cam.tf.scale;

    // Draw mode using 2D camera
    ::BeginMode2D(rl_cam);

    // Select entire source texture
    ::Rectangle source;
    source.width = tex.Width();
    source.height = tex.Height();
    source.x = 0.0f;
    source.y = 0.0f;

    // Position and scale in world
    ::Rectangle dest;
    dest.width = source.width * tf.scale;
    dest.height = source.height * tf.scale;
    dest.x = tf.position.x;
    dest.y = -(tf.position.y);

    // Local texture origin is center of image
    //(relative to top left corner)
    ::Vector2 origin;
    origin.x = dest.width * 0.5f;
    origin.y = dest.height * 0.5f;

    ::DrawTexturePro(
        *(::Texture2D *)tex.Data(),
        source, dest, origin, tf.rotation, WHITE);

    ::EndMode2D();
}
//---------------------------------------------------------------

//---------------------------------------------------------------
// TIME
//---------------------------------------------------------------
float Core::Time::DeltaTime()
{
    return ::GetFrameTime();
}
//---------------------------------------------------------------

//---------------------------------------------------------------
// UTILITY
//---------------------------------------------------------------
void Core::Log::Info(const char *msg)
{
    ::TraceLog(::LOG_INFO, msg);
}

float Core::Random(float min, float max)
{
    return ::GetRandomValue(min, max);
}
//---------------------------------------------------------------

//---------------------------------------------------------------
// INPUT
//---------------------------------------------------------------
bool Core::Input::IsKeyPressed(Core::Input::KeyCode key)
{
    return ::IsKeyPressed(key);
}
//---------------------------------------------------------------

//---------------------------------------------------------------
// MATH
//---------------------------------------------------------------
bool Core::Vector2::operator==(const Core::Vector2 &other)
{
    return ::Vector2Equals({x, y}, {other.x, other.y});
}

bool Core::Vector2::operator!=(const Core::Vector2 &other)
{
    return !(*this == other);
}

Core::Vector2 Core::Vector2::operator+(const Core::Vector2 &other)
{
    return Core::Vector2(x + other.x, y + other.y);
}

Core::Vector2 Core::Vector2::operator-(const Core::Vector2 &other)
{
    return Core::Vector2(x - other.x, y - other.y);
}

Core::Vector2 Core::Vector2::operator*(float scalar)
{
    return Core::Vector2(x * scalar, y * scalar);
}

float Core::Vector2::Dot(const Core::Vector2 &other)
{
    return x * other.x + y * other.y;
}

float Core::Vector2::Length()
{
    return ::Vector2Length({x, y});
}

Core::Vector2 Core::Vector2::Normalized()
{
    ::Vector2 res = ::Vector2Normalize({x, y});
    return Core::Vector2(res.x, res.y);
}

std::ostream &operator<<(std::ostream &os, const Core::Vector2 &vec)
{
    return os << "(" << vec.x << "," << vec.y << ")";
};
//---------------------------------------------------------------