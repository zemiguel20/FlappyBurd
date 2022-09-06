#include "NewCore.h"

namespace core
{
    RectCollider2D::RectCollider2D(Vector2 sz, Vector2 pos, Transform2D &tf)
    {
        transform = &tf;
        size = sz;
        position = pos;
    }

    bool RectCollider2D::CheckCollision(RectCollider2D &other)
    {
        // TODO: IMPLEMENT
        return false;
    }
} // namespace core
