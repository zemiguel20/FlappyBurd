#pragma once

#include <raylib.h>

struct GameObject
{
public:
	Vector2 position;
	float rotation;
	float scale;

	Texture2D* texture;
	int zind;

	Vector2 velocity;

	Vector2 boxColliderSize;

	GameObject() :
		position(Vector2(0,0)),
		rotation(0),
		scale(1.0f),
		texture(nullptr),
		zind(0),
		velocity(Vector2(0,0)),
		boxColliderSize(Vector2(-1.0f, -1.0f))
	{};
};

