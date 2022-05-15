#include "ResourceLoader.h"

#include <SDL_image.h>
#include "Renderer.h"

std::map<std::string, Sprite*> ResourceLoader::s_sprites = std::map<std::string, Sprite*>();
SDL_Renderer* ResourceLoader::s_renderContext = nullptr;

void ResourceLoader::Init(SDL_Renderer* renderContext)
{
	s_renderContext = renderContext;
}

void ResourceLoader::Destroy()
{
	// Destroy sprites
	for (const auto& [key, value] : s_sprites) {
		delete value;
	}
	s_sprites.clear();

	s_renderContext = nullptr;
}

Sprite* ResourceLoader::LoadSprite(const std::string& filename)
{
	// Search sprite cache
	auto search = s_sprites.find(filename);
	// If not found
	if (search == s_sprites.end())
	{
		//Load sprite
		std::string texPath = RES_FOLDER_PATH + filename;
		SDL_Texture* tex = IMG_LoadTexture(s_renderContext, texPath.c_str());
		Sprite* sprite = new Sprite(tex);
		//Save sprite in cache
		s_sprites.insert({ filename, sprite });

		return sprite;
	}
	// If found
	else
	{
		return search->second;
	}

}
