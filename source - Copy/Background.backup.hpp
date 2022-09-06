#pragma once

#include "Core/NewCore.h"

class Background
{
public:
    core::Transform2D *transform;
    core::SpriteRenderer *renderer;

private:
    core::Texture *texture;

public:
    Background();
    ~Background();
};

Background::Background()
{
    transform = new core::Transform2D();
    transform->scale = 0.6f;
    texture = new core::Texture("assets/background-day.png");
    renderer = new core::SpriteRenderer(*transform, *texture);
}

Background::~Background()
{
    delete transform;
    delete renderer;
    delete texture;
}
