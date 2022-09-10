#pragma once

#include "Core/Core.h"
using namespace Core;
#include <vector>

class ScrollingGround
{
private:
    const float VELOCITY = -70.0f;
    const float SPACING = 84.0f;
    const Vector2 START_POS = Vector2(-150.0f, -280.0f);
    const float X_LIMIT = -270.0f;

    std::vector<Transform2D> blocksTf;

    Sprite *sprite;

public:
    ScrollingGround()
    {

        Log::Info("Loading scrolling ground");

        Transform2D base;
        base.scale = 1.5f;
        base.position = START_POS;

        blocksTf = {base, base, base, base, base, base};

        // Set one after another
        for (int i = 0; i < blocksTf.size(); i++)
            blocksTf[i].position.x += i * SPACING;

        sprite = new Sprite("assets/dirtsprite.png");

        Log::Info("Scrolling Ground loaded");
    };

    ~ScrollingGround()
    {
        Log::Info("Unloading scrolling ground");

        blocksTf.clear();
        delete sprite;

        Log::Info("Scrolling Ground unloaded");
    };

    void Scroll()
    {
        // Move ground
        for (Transform2D &tf : blocksTf)
        {
            tf.position.x += VELOCITY * Time::DeltaTime();
        }
        // Check to move first block to the back
        if (blocksTf[0].position.x < X_LIMIT)
        {
            Transform2D block = blocksTf[0];
            block.position.x = blocksTf.back().position.x +
                               SPACING;
            blocksTf.erase(blocksTf.begin());
            blocksTf.push_back(block);
        }
    };

    void Render(const Camera2D &cam)
    {
        for (Transform2D &tf : blocksTf)
            sprite->Render(tf, cam);
    };

    bool CheckCollision(const Bird &player)
    {
        // TODO: Implement
        return false;
    };
};