#pragma once

#include "Core/Core.h"
using namespace Core;
#include "Config.h"

class Bird
{
private:
    const float JUMP_SPEED = 500.0f;
    const float GRAVITY = 1200.0f;
    const float CEILING = 300.0f;
    const Vector2 STARTING_POS = Vector2(-100.0f, 0.0f);

    Transform2D tf;
    float vel;

    Sound *jumpSound;
    Sprite *sprite;

public:
    Bird()
    {
        tf = Transform2D(STARTING_POS, 0.0f, 2.0f);
        vel = 0.0f;

        jumpSound = new Sound("assets/sfx_jump.mp3");
        sprite = new Sprite("assets/burd.png");

        Log::Info("Bird loaded");
    };

    ~Bird()
    {
        delete jumpSound;
        delete sprite;
        Log::Info("Bird unloaded");
    };

    void Move()
    {
        // Jump
        if (Input::IsKeyPressed(Input::KEY_SPACE))
        {
            vel = JUMP_SPEED;
            jumpSound->Play();
        }

        // Gravity
        vel -= GRAVITY * Time::DeltaTime();
        // Apply velocity to position
        tf.position.y += vel * Time::DeltaTime();

        // Rotation (value kept between 0-360)
        /*player.rotation += 360.0f * GetFrameTime();
        if (player.rotation >= 360.0f)
            player.rotation -= 360.0f;*/

        // Keep player from flapping infinitely
        if (tf.position.y > CEILING)
        {
            tf.position.y = CEILING;
            vel = 0.0f;
        }
    };

    void Render(const Camera2D &cam)
    {
        sprite->Render(tf, cam);
    };

    void Reset()
    {
        tf.position = STARTING_POS;
    }
};