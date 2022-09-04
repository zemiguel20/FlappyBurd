#include "Core.h"

RectCollider2D::RectCollider2D(Vector2 size, Vector2 offset, Transform2D &tf)
{
    transform = &tf;
    localCollider.width = size.x;
    localCollider.height = size.y;
    localCollider.x = -(localCollider.width * 0.5f) + offset.x;
    localCollider.y = -(localCollider.height * 0.5f) + offset.y;
}

Rectangle RectCollider2D::GetWorldRect()
{
    Rectangle newCol = localCollider;
    newCol.width *= transform->scale;
    newCol.height *= transform->scale;
    newCol.x *= transform->scale;
    newCol.y *= transform->scale;

    newCol.x += transform->position.x;
    newCol.y += transform->position.y;

    return newCol;
}