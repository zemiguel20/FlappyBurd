#pragma once

#include "Sprite.h"
#include <SDL.h>
#include <string>
#include <map>

const std::string RES_FOLDER_PATH = "res/";

/* @brief Static resource loader that also caches.
*/
class ResourceLoader
{
private:
	/* Caches loaded sprites */
	static std::map<std::string, Sprite*> s_sprites;

	static SDL_Renderer* s_renderContext;

public:
	static void Init(SDL_Renderer* renderContext);
	static void Destroy();

	static Sprite* LoadSprite(const std::string& filename);
};