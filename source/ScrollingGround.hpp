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
    const float SCALE = 1.5f;

    std::vector<Transform2D> blocksTf;

    Sprite *sprite;

    Transform2D collTf;
    RectCollider coll;

public:
    ScrollingGround()
    {

        Log::Info("Loading scrolling ground");

        Transform2D base;
        base.scale = SCALE;
        base.position = START_POS;

        blocksTf = {base, base, base, base, base, base};

        // Set one after another
        for (int i = 0; i < blocksTf.size(); i++)
            blocksTf[i].position.x += i * SPACING;

        sprite = new Sprite("assets/dirtsprite.png");

        // Collider is a wide box at the bottom
        collTf = Transform2D(Vector2(0.0f, START_POS.y),
                             0.0f, SCALE);
        coll = RectCollider(360.0f, 56.0f, Vector2());

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

#ifdef DEBUG
        coll.Render(collTf, cam);
#endif
    };

    bool CheckCollision(const Bird &player)
    {
        return coll.CheckCollision(collTf, player.coll, player.tf);
    };
};