#pragma once

#include "Core/Core.h"
using namespace Core;
#include "Config.h"

class Bird
{
private:
    Transform2D tf; // Bird transform
    Texture *tex;   // Bird texture

    float vel;

public:
    Bird()
    {
        tf = Transform2D(Vector2(-100.0f, 0.0f), 0.0f, 2.0f);
        tex = new Texture("assets/burd.png");

        vel = 0.0f;

        Log::Info("Bird loaded");
    };

    ~Bird()
    {
        delete tex;
        Log::Info("Bird unloaded");
    };

    void Update()
    {
        // Jump
        if (Input::IsKeyPressed(Input::KEY_SPACE))
        {
            vel = Config::BIRD_JUMP;
            // TODO: PlaySound(jumpSound);
        }

        // Gravity
        vel -= Config::BIRD_GRAVITY * Time::DeltaTime();
        // Apply velocity to position
        tf.position.y += vel * Time::DeltaTime();

        // Rotation (value kept between 0-360)
        /*player.rotation += 360.0f * GetFrameTime();
        if (player.rotation >= 360.0f)
            player.rotation -= 360.0f;*/

        // Keep player from flapping infinitely
        float ceiling = 300.0f;
        if (tf.position.y > ceiling)
        {
            tf.position.y = ceiling;
            vel = 0.0f;
        }
    };

    void Render(const Camera2D &cam)
    {
        RenderSprite(cam, tf, *tex);
    };
};