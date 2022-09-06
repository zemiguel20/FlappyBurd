#pragma once

//------------------------------------------------------------------------------
// APP BASE CLASS
//------------------------------------------------------------------------------

// Use as base class for the specific app.
// Concrete class should implement Start, Update and Close
class App
{
private:
    // Initialize subsystems, like window, audio, etc.
    bool AppInit();
    // Uninitialize subsystems
    void AppClose();
    // Check if window should close. Used for game loop
    bool WindowShouldClose();
    // Call at start of frame loop
    void PrepareFrame();
    // Call at end of frame loop
    void FinishFrame();

protected:
    int winW;            // Starting window width
    int winH;            // Starting window height
    const char *winName; // Window name

    virtual void Start(){};  // Initialize app variables
    virtual void Update(){}; // Update game logic. Call every frame
    virtual void Close(){};  // Cleanup app variables
public:
    App()
        : winW(1024), winH(720), winName("Empty") {}

    virtual void Run() final
    {
        if (AppInit())
        {
            Start(); // override
            while (!WindowShouldClose())
            {
                PrepareFrame();
                Update(); // override
                FinishFrame();
            }
            Close(); // override
        }

        AppClose();
    }
};

// MUST BE IMPLEMENTED. Should return an instance of the specific class
App CreateApp();
//------------------------------------------------------------------------------
#include <raylib.h>

class Transform2D
{
public:
    Vector2 position;
    float rotation; // degrees
    float scale;

    Transform2D();
};

class SpriteRenderer
{
private:
    Transform2D *transform;
    Texture2D *texture;

public:
    SpriteRenderer(Transform2D &, Texture2D &);
    void Render(Camera2D);
};

class RectCollider2D
{
private:
    Transform2D *transform;
    Rectangle localCollider;

public:
    RectCollider2D(Vector2 size, Vector2 offset, Transform2D &);

    // Gets the collider rect with transform applied
    Rectangle GetWorldRect();
};
