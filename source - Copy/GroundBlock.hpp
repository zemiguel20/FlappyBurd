#pragma once

#include "Core/NewCore.h"

class GroundBlock
{
public:
    core::Transform2D *transform;
    core::SpriteRenderer *renderer;
    core::RectCollider2D *collider;

private:
    core::Texture *texture;

public:
    GroundBlock();
    ~GroundBlock();
};

GroundBlock::GroundBlock()
{
    if (texture == nullptr)
        texture = new core::Texture("assets/dirtsprite.png");

    transform = new core::Transform2D();
    transform->scale = 2.0f;
    // Position at bottom of window
    transform->position.y = (GetScreenHeight() / 2) - (texture->Height() * transform->scale);

    renderer = new core::SpriteRenderer(*transform, *texture);

    collider = new core::RectCollider2D(
        core::Vector2(texture->Width(), texture->Height()),
        core::Vector2(),
        *transform);
}

GroundBlock::~GroundBlock()
{
    if (texture)
        delete texture;

    delete transform;
    delete renderer;
    delete collider;
}
