#pragma once

#include <ostream>

namespace Core
{
    //-----------------------------------------------------------
    // APP BASE CLASS
    //-----------------------------------------------------------

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

        // Initialize application
        virtual void Start(){};

        // Called before Update.
        // Tasks like cleaning render buffer are done here.
        virtual void PrepareFrame() final;

        // Update application state
        virtual void Update(){};

        // Render frame for current application state
        virtual void Render(){};

        // Called after Render.
        // Tasks like swapping render buffers are done here.
        virtual void FinishFrame() final;

        // Cleanup application and close
        virtual void Close(){};

        // Shutdown core systems
        virtual void Shutdown() final;

        // Virtual destructor allows deleting instances
        virtual ~App(){};
    };

    // MUST BE IMPLEMENTED!
    // Returns instance of derived App object.
    App *CreateApp();
    //-----------------------------------------------------------

    //-----------------------------------------------------------
    // WINDOW MANAGEMENT FUNCTIONS
    //-----------------------------------------------------------

    // Sets the window size/resolution
    void SetWindowSize(int width, int height);
    // Sets the window title
    void SetWindowTitle(const char *title);
    //-----------------------------------------------------------

    //-----------------------------------------------------------
    // MATH
    //-----------------------------------------------------------

    // 2-dimensional Euclidean Vector
    class Vector2
    {
    public:
        float x;
        float y;

        Vector2() : x(0.0f), y(0.0f){};
        Vector2(float x, float y) : x(x), y(y){};

        // Equality
        bool operator==(const Vector2 &other);
        bool operator!=(const Vector2 &other);
        // Addition
        Vector2 operator+(const Vector2 &other);
        // Subtraction
        Vector2 operator-(const Vector2 &other);
        // Scalar multiplication
        Vector2 operator*(float scalar);
        // Dot product
        float Dot(const Vector2 &other);
        // Magnitude of vector
        float Length();
        // Unit vector.
        // Calculates the normalized version of this vector
        Vector2 Normalized();

        // Printing the vector
        friend std::ostream &operator<<(std::ostream &os,
                                        const Vector2 &vec);
    };
    //-----------------------------------------------------------

    //-----------------------------------------------------------
    // TRANSFORM
    //-----------------------------------------------------------

    // 2D Transform, X axis is right, Y axis is up
    class Transform2D
    {
    public:
        Vector2 position;
        float rotation; // degrees
        float scale;

        Transform2D()
            : position(Vector2()),
              rotation(0.0f),
              scale(1.0f){};
        Transform2D(Vector2 pos, float rot, float scl)
            : position(pos),
              rotation(rot),
              scale(scl){};
    };
    //-----------------------------------------------------------

    //-----------------------------------------------------------
    // CAMERA
    //-----------------------------------------------------------

    // 2D Camera used for rendering.
    class Camera2D
    {
    public:
        Transform2D tf; // Camera transform, Scale is the zoom

        Camera2D() : tf(Transform2D()){};
        Camera2D(Vector2 pos, float rot, float zoom)
            : tf(Transform2D(pos, rot, zoom)){};
    };
    //-----------------------------------------------------------

    //-----------------------------------------------------------
    // RENDERING
    //-----------------------------------------------------------

    class Sprite
    {
    private:
        void *rl_texture;

    public:
        // Loads sprite from a file
        Sprite(const char *filepath);
        ~Sprite();

        void Render(const Transform2D &, const Camera2D &);
    };
    //-----------------------------------------------------------

    //-----------------------------------------------------------
    // TIME
    //-----------------------------------------------------------
    namespace Time
    {
        // Get delta time between frames
        float DeltaTime();
    } // namespace Time
    //-----------------------------------------------------------

    //-----------------------------------------------------------
    // UTILITY
    //-----------------------------------------------------------
    namespace Log
    {
        // Log a Info message to log file
        void Info(const char *);
    } // namespace Log

    // Get random number in range [min, max]
    float Random(float min, float max);

    class Timer
    {
    private:
        float timeCount;
        float limit;

    public:
        Timer(float seconds) : timeCount(0.0f),
                               limit(seconds){};

        void Tick() { timeCount += Time::DeltaTime(); };
        bool Finished() { return timeCount >= limit; };
        void Reset() { timeCount = 0.0f; };
    };
    //-----------------------------------------------------------

    //-----------------------------------------------------------
    // INPUT
    //-----------------------------------------------------------
    namespace Input
    {
        enum KeyCode
        {
            KEY_SPACE = 32
        };

        // Check if a key has been pressed this frame
        bool IsKeyPressed(KeyCode);
    } // namespace Input
    //-----------------------------------------------------------

    //-----------------------------------------------------------
    // SOUND
    //-----------------------------------------------------------

    class Sound
    {
    public:
        Sound(const char *filepath);
        ~Sound();

        void Play();
    };
    //-----------------------------------------------------------

} // namespace Core