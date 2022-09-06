#include "NewCore.h"

#include <raylib.h>

namespace core
{
    SpriteRenderer::SpriteRenderer(Transform2D &tf, Texture &tex)
    {
        transform = &tf;
        texture = &tex;
    }

    void SpriteRenderer::Render(Camera2D cam)
    {
        // NOTE: raylib uses downwards Y world axis

        // Create raylib camera object
        ::Camera2D rl_cam;
        rl_cam.offset.x = ::GetScreenWidth() / 2;
        rl_cam.offset.y = ::GetScreenHeight() / 2;
        rl_cam.target.x = cam.transform.position.x;
        rl_cam.target.y = -(cam.transform.position.y);
        rl_cam.rotation = cam.transform.rotation;
        rl_cam.zoom = cam.transform.scale;

        // Draw mode using 2D camera
        ::BeginMode2D(rl_cam);

        // Select entire source texture
        ::Rectangle source;
        source.width = texture->Width();
        source.height = texture->Height();
        source.x = 0.0f;
        source.y = 0.0f;

        // Position and scale in world
        ::Rectangle dest;
        dest.width = source.width * transform->scale;
        dest.height = source.height * transform->scale;
        dest.x = transform->position.x;
        dest.y = -(transform->position.y);

        // Local texture origin is center of image (relative to top left corner)
        ::Vector2 origin;
        origin.x = dest.width * 0.5f;
        origin.y = dest.height * 0.5f;

        ::DrawTexturePro(
            *(::Texture2D *)texture->Data(),
            source, dest, origin, transform->rotation, WHITE);

        ::EndMode2D();
    }
} // namespace core
