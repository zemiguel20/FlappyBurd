#pragma once

//------------------------------------------------------------------------------
// APP BASE CLASS
//------------------------------------------------------------------------------
// Base App class.
// Derived class should override functions to implement specific app behaviour.
// Provided Main creates app and calls functions.
class App
{
    // TODO: use startup flags with defaults that can be overriden by derived
public:
    // Initialize core systems (window, audio, etc.)
    // Returns success result of initialization
    virtual bool Init() final;

    // Shutdown core systems and application
    virtual void Shutdown() final;

    // Initialize application state and variables
    virtual void Start(){};

    // Called before Update.
    // Tasks like cleaning render buffer are done here.
    virtual void PrepareFrame();

    // Update application state
    virtual void Update(){};

    // Called after Update.
    // Tasks like swapping render buffers are done here.
    virtual void FinishFrame();

    // Cleanup application state and variables
    virtual void Close(){};

    // Virtual destructor allows deleting instances
    virtual ~App(){};
};

// MUST BE IMPLEMENTED!
// Implementation should return the desired derived App instance.
// Returns instance of derived App object.
App *CreateApp();
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// WINDOW MANAGEMENT FUNCTIONS
//------------------------------------------------------------------------------
namespace Window
{
    // Sets the window size/resolution
    void SetSize(int width, int height);
    // Sets the window title
    void SetTitle(const char *title);
} // namespace Window
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
