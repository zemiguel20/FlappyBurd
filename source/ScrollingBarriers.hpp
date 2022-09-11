#pragma once

#include "Core/Core.h"
using namespace Core;
#include <vector>

class ScrollingBarriers
{
private:
    const float VELOCITY = -70.0f;
    const float SPACING = 270.0f;
    const float START_X = 360.0f;
    const float X_LIMIT = -220.0f;
    const float GAP_SIZE = 120.0f;
    const float MIN_Y_SPAWN = -150.0f;
    const float MAX_Y_SPAWN = 200.0f;

    std::vector<Transform2D> barriersTf;

    RectCollider gapColl;

    Sprite *sprite;

    bool passed;

public:
    ScrollingBarriers()
    {
        Log::Info("Loading scrolling barriers");

        // Base position off screen
        Transform2D base;
        base.scale = 2.0f;
        base.position.x = START_X;

        barriersTf = {base, base};

        // Set each barrier with spacing and random Y
        for (int i = 0; i < barriersTf.size(); i++)
        {
            barriersTf[i].position.x += i * SPACING;
            barriersTf[i].position.y =
                Random(MIN_Y_SPAWN, MAX_Y_SPAWN);
        }

        sprite = new Sprite("assets/log.png");

        gapColl = RectCollider(2.0f, GAP_SIZE, Vector2(10.f, 0.0f));

        passed = false;

        Log::Info("Scrolling barriers loaded");
    };

    ~ScrollingBarriers()
    {
        Log::Info("Unloading scrolling barriers");

        barriersTf.clear();
        delete sprite;

        Log::Info("Scrolling barriers unloaded");
    };

    void Scroll()
    {
        // Move barriers
        for (Transform2D &tf : barriersTf)
        {
            tf.position.x += VELOCITY * Time::DeltaTime();
        }
        // Check to move first block to the back
        if (barriersTf[0].position.x < X_LIMIT)
        {
            Transform2D barrier = barriersTf[0];
            // Set new X position with spacing
            barrier.position.x = barriersTf.back().position.x +
                                 SPACING;
            barrier.position.y =
                Random(MIN_Y_SPAWN, MAX_Y_SPAWN);

            barriersTf.erase(barriersTf.begin());
            barriersTf.push_back(barrier);

            // Reset barrier passed
            passed = false;
        }
    };

    void Render(const Camera2D &cam)
    {
        for (Transform2D &barrier : barriersTf)
        {
            float logPosOffset =
                (GAP_SIZE * 0.5f) + (125.0f * barrier.scale);

            Transform2D topPart = barrier;
            topPart.position.y += logPosOffset;
            Transform2D botPart = barrier;
            botPart.position.y -= logPosOffset;

            sprite->Render(topPart, cam);
            sprite->Render(botPart, cam);
        }

#ifdef DEBUG
        gapColl.Render(barriersTf[0], cam);

        DrawLine(Vector2(-500.0f, MAX_Y_SPAWN),
                 Vector2(500.0f, MAX_Y_SPAWN),
                 cam);

        DrawLine(Vector2(-500.0f, MIN_Y_SPAWN),
                 Vector2(500.0f, MIN_Y_SPAWN),
                 cam);
#endif
    };

    bool CheckGapPassed(const Bird &player)
    {
        // Gap should only be passed once
        // So if first gap passed, return false as if
        // relative to the next one
        // State is reset after first one is moved to back
        if (passed)
            return false;

        passed = gapColl.CheckCollision(barriersTf[0],
                                        player.coll,
                                        player.tf);
        return passed;
    };

    bool CheckCollision(const Bird &player)
    {
        // TODO: implement
        return false;
    }

    void Reset()
    {
        // TODO: implement
    }
};