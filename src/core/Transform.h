#pragma once

#include "Math.h"

struct Transform
{
	vec2 position;
	float rotation;
	float scale;

	Transform() : position(vec2()), rotation(0.0f), scale(1.0f) {}
	Transform(vec2 position, float rotation, float scale) :
		position(position), rotation(rotation), scale(scale) {}
};