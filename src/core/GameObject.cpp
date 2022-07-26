#include "GameObject.h"

GameObject::GameObject(vec2 position, float rotation, float scale, Sprite* sprite, int zind)
{
	this->transform = Transform(position, rotation, scale);
	this->sprite = sprite;
	this->zind = zind;
	this->velocity = vec2();
}

GameObject::~GameObject()
{
}
