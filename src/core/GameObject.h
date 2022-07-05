#pragma once

#include "Sprite.h"
#include "Transform.h"
#include "Math.h"

class GameObject
{
public:
	Transform transform;
	Sprite* sprite;
	vec2 velocity;

	GameObject(Transform& transform, Sprite* sprite);
	~GameObject();
};

