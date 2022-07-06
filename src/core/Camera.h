#pragma once

#include "Transform.h"

class Camera
{
public:
	Transform transform;

	Camera();
	~Camera();
	void UpdateViewportTransform();
	vec2 WorldToViewportPoint(vec2 point) const;
};

