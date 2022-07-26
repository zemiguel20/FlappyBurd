#pragma once

#include "Sprite.h"
#include "Transform.h"
#include "Math.h"

class GameObject
{
public:
	Transform transform;

	Sprite* sprite;
	int zind;

	vec2 velocity;

	GameObject(vec2 position, float rotation, float scale, Sprite* sprite, int zind);
	~GameObject();
};

