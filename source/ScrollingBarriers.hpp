#pragma once

#include "Core/Core.h"
using namespace Core;
#include "Config.h"
#include <vector>

class ScrollingBarriers
{
private:
    Texture *tex;
    std::vector<Transform2D> barriersTf;

public:
    ScrollingBarriers()
    {
        tex = new Texture("assets/log.png");

        // Base position off screen
        Transform2D base;
        base.scale = 2.0f;
        base.position.x = Config::REF_SCREEN_W;

        barriersTf = {base, base};

        // Set each barrier with spacing and random Y
        for (int i = 0; i < barriersTf.size(); i++)
        {
            barriersTf[i].position.x +=
                i *
                (tex->Width() * base.scale +
                 Config::BARRIER_SPACING);

            barriersTf[i].position.y =
                Random(Config::BARRIER_MIN_SPAWN,
                       Config::BARRIER_MAX_SPAWN);
        }

        Log::Info("Scrolling barriers loaded");
    };

    ~ScrollingBarriers()
    {
        delete tex;
        Log::Info("Scrolling barriers unloaded");
    };

    void Update()
    {
        // Move barriers
        for (Transform2D &tf : barriersTf)
        {
            tf.position.x -= Config::SCROLL_VEL *
                             Time::DeltaTime();
        }
        // Check to move first block to the back
        bool firstNotVisible =
            barriersTf[0].position.x <
            -(Config::REF_SCREEN_W / 2) - 50.0f;
        if (firstNotVisible)
        {
            Transform2D barrier = barriersTf[0];
            // Set new X position with spacing
            barrier.position.x = barriersTf.back().position.x +
                                 (tex->Width() * barrier.scale) +
                                 Config::BARRIER_SPACING;
            barrier.position.y =
                Random(Config::BARRIER_MIN_SPAWN,
                       Config::BARRIER_MAX_SPAWN);

            barriersTf.erase(barriersTf.begin());
            barriersTf.push_back(barrier);
        }
    };

    void Render(const Camera2D &cam)
    {
        for (Transform2D &barrier : barriersTf)
        {
            float logPosOffset =
                (Config::GAP_SIZE / 2) +
                (tex->Height() / 2 * barrier.scale);

            Transform2D topPart = barrier;
            topPart.position.y += logPosOffset;
            Transform2D botPart = barrier;
            botPart.position.y -= logPosOffset;

            RenderSprite(cam, topPart, *tex);
            RenderSprite(cam, botPart, *tex);
        }
    };
};