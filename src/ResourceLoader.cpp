#include "ResourceLoader.h"

#include <SDL_image.h>
#include "core/Renderer.h"

Sprite ResourceLoader::LoadSprite(std::string imgpath)
{
	SDL_Texture* tex = IMG_LoadTexture(Renderer::GetRenderContext(), imgpath.c_str());
	return Sprite(tex);
}
