#pragma once

#include "core/Sprite.h"

#include <string>

// TODO: make static instance that caches resources
namespace ResourceLoader
{
	Sprite LoadSprite(std::string imgpath);
}