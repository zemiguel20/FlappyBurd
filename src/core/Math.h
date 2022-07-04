#pragma once

#include <iostream>

struct vec2
{
	float x, y;

	vec2() : x(0.0f), y(0.0f) {}
	vec2(float x, float y) : x(x), y(y) {}

	vec2 operator+(const vec2& other) { return vec2(x + other.x, y + other.y); }
	vec2& operator+=(const vec2& other) { x += other.x; y += other.y; return *this; }

	vec2 operator-(const vec2& other) { return vec2(x - other.x, y - other.y); }
	vec2& operator-=(const vec2& other) { x -= other.x; y -= other.y; return *this; }

	vec2 operator*(float scalar) { return vec2(x * scalar, y * scalar); }
	vec2& operator*=(float scalar) { x *= scalar; y *= scalar; return *this; }

	friend std::ostream& operator<<(std::ostream& os, const vec2& vec) { return os << "(" << vec.x << "," << vec.y << ")"; };
};