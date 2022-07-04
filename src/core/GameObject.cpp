#include "GameObject.h"

GameObject::GameObject(Transform& transform, Sprite* sprite)
{
	this->transform = transform;
	this->sprite = sprite;
}

GameObject::~GameObject()
{
}
