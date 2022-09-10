#pragma once

#include "Core/Core.h"
using namespace Core;

class Background
{
private:
    Transform2D tf;
    Sprite *sprite;

public:
    Background()
    {
        Log::Info("Loading background...");

        tf = Transform2D();
        tf.scale = 0.6f;

        const char *bgs[] = {"assets/background-morning.png",
                             "assets/background-day.png",
                             "assets/background-dusk.png",
                             "assets/background-night.png"};
        sprite = new Sprite(bgs[Random(0, 3)]);

        Log::Info("Background loaded");
    }

    ~Background()
    {
        Log::Info("Unloading background...");

        delete sprite;

        Log::Info("Background unloaded");
    }

    void Render(const Camera2D &cam)
    {
        sprite->Render(tf, cam);
    }
};