#pragma once

#include <ostream>

namespace core
{
    bool Init();
    void Close();

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
        // Unit vector. Calculates the normalized version of this vector
        Vector2 Normalized();

        // Printing the vector
        friend std::ostream &operator<<(std::ostream &os, const Vector2 &vec);
    };

    // Wrapper Texture class
    class Texture
    {
    private:
        void *rl_texture;

    public:
        Texture(const char *filepath);
        ~Texture();

        int Width();
        int Height();
        // Returns original texture data (in this case the raylib texture data)
        void *Data();
    };

    // 2D Transform, X is right, Y is up
    class Transform2D
    {
    public:
        Vector2 position;
        float rotation; // degrees
        float scale;

        Transform2D();
    };

    // 2D Camera. Scale is the zoom used to scale the entire scene
    class Camera2D
    {
    public:
        Transform2D transform;

        Camera2D();
    };

    // Renders the Sprite in the world to screen using a Camera
    class SpriteRenderer
    {
    private:
        Transform2D *transform;
        Texture *texture;

    public:
        SpriteRenderer(Transform2D &, Texture &);
        void Render(Camera2D);
    };

    // Represents a rectangle collider.
    // Position and dimensions are relative to object's transform.
    class RectCollider2D
    {
    private:
        Transform2D *transform;

    public:
        Vector2 position; // Position relative to transform
        Vector2 size;     // Unscaled dimensions

        RectCollider2D(Vector2 size, Vector2 position, Transform2D &);

        // Checks collision with other collider
        bool CheckCollision(RectCollider2D &);
    };

} // namespace fb