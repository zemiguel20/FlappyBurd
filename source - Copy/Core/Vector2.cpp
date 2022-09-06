#include "NewCore.h"

#include <raymath.h>

namespace core
{
    bool Vector2::operator==(const Vector2 &other)
    {
        return ::Vector2Equals({x, y}, {other.x, other.y});
    }

    bool Vector2::operator!=(const Vector2 &other)
    {
        return !(*this == other);
    }

    Vector2 Vector2::operator+(const Vector2 &other)
    {
        return Vector2(x + other.x, y + other.y);
    }

    Vector2 Vector2::operator-(const Vector2 &other)
    {
        return Vector2(x - other.x, y - other.y);
    }

    Vector2 Vector2::operator*(float scalar)
    {
        return Vector2(x * scalar, y * scalar);
    }

    float Vector2::Dot(const Vector2 &other)
    {
        return x * other.x + y * other.y;
    }

    float Vector2::Length()
    {
        return ::Vector2Length({x, y});
    }

    Vector2 Vector2::Normalized()
    {
        ::Vector2 res = ::Vector2Normalize({x, y});
        return Vector2(res.x, res.y);
    }

    std::ostream &operator<<(std::ostream &os, const Vector2 &vec)
    {
        return os << "(" << vec.x << "," << vec.y << ")";
    };
}