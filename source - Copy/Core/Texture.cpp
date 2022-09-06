#include "NewCore.h"

#include <raylib.h>

namespace core
{
    Texture::Texture(const char *filepath)
    {
        rl_texture = new ::Texture;
        *(::Texture *)rl_texture = ::LoadTexture(filepath);
    }

    Texture::~Texture()
    {
        ::UnloadTexture(*(::Texture *)rl_texture);
        delete (::Texture *)rl_texture;
    }

    int Texture::Width()
    {
        return ((::Texture *)rl_texture)->width;
    }

    int Texture::Height()
    {
        return ((::Texture *)rl_texture)->height;
    }

    void *Texture::Data()
    {
        return rl_texture;
    }
} // namespace core
