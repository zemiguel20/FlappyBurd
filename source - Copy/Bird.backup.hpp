#pragma once

#include "Core/NewCore.h"

class Bird
{
public:
    core::Transform2D *transform;
    core::SpriteRenderer *renderer;
    core::RectCollider2D *collider;

private:
    core::Texture *texture; // Bird texture asset

    Sound jumpSound; // Bird jump sound asset

    float velocity; // Y velocity

public:
    Bird();
    ~Bird();
    void Update();
};

Bird::Bird()
{
    transform = new core::Transform2D();
    transform->scale = 2.0f;

    texture = new core::Texture("assets/burd.png");
    jumpSound = LoadSound("assets/sfx_jump.mp3");

    renderer = new core::SpriteRenderer(*transform, *texture);
    collider = new core::RectCollider2D(
        core::Vector2(20.0f, 12.0f),
        core::Vector2(),
        *transform);

    velocity = 0.0f;
}

Bird::~Bird()
{
    delete transform;
    delete renderer;
    delete collider;
    delete texture;
    UnloadSound(jumpSound);
}

void Bird::Update()
{
    // Jump
    if (IsKeyPressed(KEY_SPACE))
    {
        velocity = -500.0f;
        PlaySound(jumpSound);
    }

    // Acceleration
    velocity += 1200.0f * GetFrameTime();
    // Apply velocity to position
    transform->position.y += velocity * GetFrameTime();

    // Rotation (value kept between 0-360)
    /*player.rotation += 360.0f * GetFrameTime();
    if (player.rotation >= 360.0f)
        player.rotation -= 360.0f;*/

    // Keep bird within screen limits
    float ceiling = -300.0f;
    if (transform->position.y < ceiling)
    {
        transform->position.y = ceiling;
        velocity = 0.0f;
    }
}