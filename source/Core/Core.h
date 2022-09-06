#pragma once

namespace Core
{
    //--------------------------------------------------------------------------
    // APP BASE CLASS
    //--------------------------------------------------------------------------

    // Base App class.
    // Derived class should override functions to implement
    // specific app behaviour.
    // Provided Main creates app and calls functions.
    class App
    {
        // TODO: use startup flags with defaults that can be overriden by derived
    public:
        // Initialize core systems (window, audio, etc.)
        // Returns success result of initialization
        virtual bool Init() final;

        // Shutdown core systems
        virtual void Shutdown() final;

        // Initialize application
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

        // Cleanup application and close
        virtual void Close(){};

        // Virtual destructor allows deleting instances
        virtual ~App(){};
    };

    // MUST BE IMPLEMENTED!
    // Implementation should return the desired derived App instance.
    // Returns instance of derived App object.
    App *CreateApp();
    //--------------------------------------------------------------------------

    //--------------------------------------------------------------------------
    // WINDOW MANAGEMENT FUNCTIONS
    //--------------------------------------------------------------------------

    // Sets the window size/resolution
    void SetWindowSize(int width, int height);
    // Sets the window title
    void SetWindowTitle(const char *title);

    //--------------------------------------------------------------------------

    //--------------------------------------------------------------------------
    // CAMERA
    //--------------------------------------------------------------------------

    // 2D Camera
    class Camera2D
    {
    };

    //--------------------------------------------------------------------------

} // namespace Core