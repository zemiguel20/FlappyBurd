#include "ResourceLoader.h"

#include <SDL_image.h>

Sprite ResourceLoader::LoadSprite(Renderer& renderer, std::string imgpath)
{
	SDL_Texture* tex = IMG_LoadTexture(renderer.GetRenderContext(), imgpath.c_str());
	int w, h;
	SDL_QueryTexture(tex, NULL, NULL, &w, &h); // get the width and height of the texture

	return Sprite(tex, w, h);
}
