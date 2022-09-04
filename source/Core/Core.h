#pragma once

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
