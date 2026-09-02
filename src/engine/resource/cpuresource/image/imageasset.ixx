module;
#include "SDL3/SDL_render.h"

export module engine.resource.imageasset;
import engine.utilities;
import std;


export namespace engine::resource
{
    using PixelFormat = std::uint32_t;

    struct ImageAsset
    {
        int width{};
        int height{};
        PixelFormat format{};
        std::vector<std::byte> pixels{};
    };
}
