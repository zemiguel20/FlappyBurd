#pragma once

#include "Sprite.h"
#include "Math.h"

struct Transform
{
	vec2 position;
	float rotation;
	float scale;

	Transform() : position(vec2()), rotation(0.0f), scale(0.0f) {}
	Transform(vec2 position, float rotation, float scale) :
		position(position), rotation(rotation), scale(scale) {}
};

class GameObject
{
public:
	Transform transform;
	Sprite* sprite;
	vec2 velocity;

	GameObject(Transform& transform, Sprite* sprite);
	~GameObject();
};

