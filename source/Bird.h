#pragma once

#include <raylib.h>
#include "Core/Core.h"

class Bird
{
public:
    Transform2D *transform;
    SpriteRenderer *renderer;
    RectCollider2D *collider;

private:
    Texture2D texture; // Bird texture asset

    Sound jumpSound; // Bird jump sound asset

    float velocity; // Y velocity

public:
    Bird();
    ~Bird();
    void Update();
};