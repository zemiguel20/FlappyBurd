#include "Core.h"

SpriteRenderer::SpriteRenderer(Transform2D &tf, Texture2D &tex)
{
    transform = &tf;
    texture = &tex;
}

void SpriteRenderer::Render(Camera2D cam)
{
    BeginMode2D(cam);

    Rectangle source;
    source.width = texture->width;
    source.height = texture->height;
    source.x = 0.0f;
    source.y = 0.0f;

    Rectangle dest;
    dest.width = source.width * transform->scale;
    dest.height = source.height * transform->scale;
    dest.x = transform->position.x;
    dest.y = transform->position.y;

    Vector2 origin;
    origin.x = dest.width * 0.5f;
    origin.y = dest.height * 0.5f;

    DrawTexturePro(*texture, source, dest, origin, transform->rotation, WHITE);

    EndMode2D();
}