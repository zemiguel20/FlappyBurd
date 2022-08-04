#pragma once

#include "Sprite.h"
#include "Transform.h"
#include "Math.h"

struct GameObject
{
public:
	Transform transform;

	Sprite* sprite;
	int zind;

	vec2 velocity;

	vec2 boxColliderSize;

	GameObject() :
		transform(Transform()),
		sprite(nullptr),
		zind(0),
		velocity(vec2()),
		boxColliderSize(vec2(-1.0f, -1.0f))
	{};
};

