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

            static auto pollEvent() -> std::optional<core::Event>;
    };


}

namespace engine::platform
{
    auto SdlPlatform::pollEvent() -> std::optional<core::Event>
    {
        SDL_Event event;

        if (!SDL_PollEvent(&event))
        {
            return std::nullopt;
        }

        return translateSDLEvent(event);
    }

}
