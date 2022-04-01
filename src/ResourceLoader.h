#pragma once

#include "Renderer.h"
#include "Sprite.h"

#include <string>

namespace ResourceLoader
{
	Sprite LoadSprite(Renderer& renderer, std::string imgpath);
}