#include "Core.h"

#include <raylib.h>
#define RAYMATH_IMPLEMENTATION
#include <raymath.h>

#ifndef DEBUG // Hide console in Release
#ifdef _WIN32
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif
#endif

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
#ifdef DEBUG
            ::DrawFPS(0, 0);
#endif
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
    ClearBackground(::RAYWHITE);
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
// RENDERING
//---------------------------------------------------------------

Core::Sprite::Sprite(const char *filepath)
{
    rl_texture = new ::Texture;
    *(::Texture *)rl_texture = ::LoadTexture(filepath);
}

Core::Sprite::~Sprite()
{
    ::UnloadTexture(*(::Texture *)rl_texture);
    delete (::Texture *)rl_texture;
}

void Core::Sprite::Render(const Transform2D &tf,
                          const Camera2D &cam)
{
    // NOTE: raylib uses downwards Y world axis

    // Get texture
    ::Texture tex = *(::Texture *)rl_texture;

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
    source.width = tex.width;
    source.height = tex.height;
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

    ::DrawTexturePro(tex, source, dest, origin,
                     tf.rotation, ::WHITE);

    ::EndMode2D();
}

void Core::DrawLine(Vector2 p1, Vector2 p2, const Camera2D &cam)
{
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

    ::DrawLine(p1.x, -p1.y, p2.x, -p2.y, ::WHITE);

    ::EndMode2D();
}

void Core::DrawRectangle(Vector2 topleft, Vector2 botright,
                         Color color)
{
    ::Color rl_color;
    rl_color.r = (color & 0xFF000000) >> 24;
    rl_color.g = (color & 0x00FF0000) >> 16;
    rl_color.b = (color & 0x0000FF00) >> 8;
    rl_color.a = (color & 0x000000FF);

    ::DrawRectangle(topleft.x, topleft.y,
                    (botright.x - topleft.x),
                    (botright.y - topleft.y),
                    rl_color);
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

int Core::Random(int min, int max)
{
    return ::GetRandomValue(min, max);
}

bool Core::FileExists(const char *filepath)
{
    return ::FileExists(filepath);
}

char *Core::LoadFileText(const char *filename)
{
    return ::LoadFileText(filename);
}

void Core::UnloadFileText(char *text)
{
    ::UnloadFileText(text);
}

bool Core::SaveFileText(const char *fileName, char *text)
{
    return ::SaveFileText(fileName, text);
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
// SOUND
//---------------------------------------------------------------
Core::Sound::Sound(const char *filepath)
{
    rl_sound = new ::Sound;
    *(::Sound *)rl_sound = ::LoadSound(filepath);
}

Core::Sound::~Sound()
{
    ::UnloadSound(*(::Sound *)rl_sound);
    delete (::Sound *)rl_sound;

    Log::Info("SOUND: Unloaded sound");
}

void Core::Sound::Play()
{
    ::PlaySound(*(::Sound *)rl_sound);
}
//---------------------------------------------------------------

//---------------------------------------------------------------
// COLLISION
//---------------------------------------------------------------
bool Core::RectCollider::CheckCollision(const Transform2D &tf,
                                        const RectCollider &otherCol,
                                        const Transform2D &otherTf)
{
    ::Rectangle rect;
    rect.width = width * tf.scale;
    rect.height = height * tf.scale;
    rect.x = -(rect.width * 0.5f) +
             (offsetPos.x * tf.scale) +
             tf.position.x;
    rect.y = -(rect.height * 0.5f) +
             (offsetPos.y * tf.scale) +
             -(tf.position.y);

    ::Rectangle otherRect;
    otherRect.width = otherCol.width * otherTf.scale;
    otherRect.height = otherCol.height * otherTf.scale;
    otherRect.x = -(otherRect.width * 0.5f) +
                  (otherCol.offsetPos.x * otherTf.scale) +
                  otherTf.position.x;
    otherRect.y = -(otherRect.height * 0.5f) +
                  (otherCol.offsetPos.y * otherTf.scale) +
                  -(otherTf.position.y);

    return ::CheckCollisionRecs(rect, otherRect);
};

void Core::RectCollider::Render(const Transform2D &tf,
                                const Camera2D &cam)
{

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

    ::Rectangle rect;
    rect.width = width * tf.scale;
    rect.height = height * tf.scale;
    rect.x = -(rect.width * 0.5f) +
             (offsetPos.x * tf.scale) +
             tf.position.x;
    rect.y = -(rect.height * 0.5f) +
             (offsetPos.y * tf.scale) +
             -(tf.position.y);

    ::DrawRectangleLinesEx(rect, 2.0f, ::PURPLE);

    ::EndMode2D();
};

//---------------------------------------------------------------

//---------------------------------------------------------------
// TEXT
//---------------------------------------------------------------
Core::Font::Font(const char *filepath)
{
    rl_font = new ::Font;
    *(::Font *)rl_font = ::LoadFont(filepath);
}

Core::Font::~Font()
{
    ::UnloadFont(*(::Font *)rl_font);
    delete (::Font *)rl_font;
}

void *Core::Font::Data()
{
    return (::Font *)rl_font;
}

void Core::Text::Render(int x, int y)
{
    ::Vector2 position;
    position.x = x;
    position.y = y;
    ::Vector2 origin = ::MeasureTextEx(*(::Font *)font->Data(),
                                       text.c_str(), size, 0.0f);
    origin.x *= 0.5f;
    origin.y *= 0.5f;

    ::Color rl_color;
    rl_color.r = (color & 0xFF000000) >> 24;
    rl_color.g = (color & 0x00FF0000) >> 16;
    rl_color.b = (color & 0x0000FF00) >> 8;
    rl_color.a = (color & 0x000000FF);

    DrawTextPro(*(::Font *)font->Data(), text.c_str(),
                position, origin, 0.0f, size, 0.0f, rl_color);
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