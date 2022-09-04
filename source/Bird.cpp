#include "Bird.h"

Bird::Bird()
{
    transform = new Transform2D();
    transform->scale = 2.0f;

    texture = LoadTexture("assets/burd.png");
    jumpSound = LoadSound("assets/sfx_jump.mp3");

    renderer = new SpriteRenderer(*transform, texture);
    collider = new RectCollider2D({20.0f, 12.0f}, {0.0f, 0.0f}, *transform);

    velocity = 0.0f;
}

Bird::~Bird()
{
    delete transform;
    delete renderer;
    delete collider;

    UnloadTexture(texture);
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