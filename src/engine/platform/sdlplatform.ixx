module;
#include "SDL3/SDL_init.h"

export module engine.platform.sdlplatform;
export import :sdleventadapter;
export import :sdlinputadapter;
import engine.platform.inputcode;
import engine.core.eventtype;
import std;

export namespace engine::platform
{
    class SdlPlatform
    {
        public:
            SdlPlatform()
            {
                if (!SDL_Init(SDL_INIT_VIDEO))
                throw std::runtime_error(SDL_GetError());
            }

            ~SdlPlatform()
            {
                SDL_Quit();
            }
    };
}

namespace engine::platform
{



}
