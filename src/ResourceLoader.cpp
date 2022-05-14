#include "ResourceLoader.h"

#include <SDL_image.h>
#include "core/Renderer.h"

Sprite ResourceLoader::LoadSprite(std::string imgpath)
{
	SDL_Texture* tex = IMG_LoadTexture(Renderer::GetRenderContext(), imgpath.c_str());
	int w, h;
	SDL_QueryTexture(tex, NULL, NULL, &w, &h); // get the width and height of the texture

	return Sprite(tex, w, h);
}
