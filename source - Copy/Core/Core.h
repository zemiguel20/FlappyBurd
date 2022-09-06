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

    // Render frame for current application state
    virtual void Render(){};

    // Called after Render.
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

//------------------------------------------------------------------------------
// CAMERA
//------------------------------------------------------------------------------
namespace Core
{
    // 2D Camera
    class Camera2D
    {
    };
} // namespace cam

//------------------------------------------------------------------------------