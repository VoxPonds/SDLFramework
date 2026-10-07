module;
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_hints.h"
#include "SDL3/SDL_render.h"

export module engine.platform.sdlplatform;
export import :sdleventadapter;
export import :sdlinputadapter;

import engine.core.eventtype;
import engine.core.math;
import engine.platform.inputcode;
import engine.platform.sdlptr;
import engine.utilities;
import std;

export namespace engine::platform
{
    class SdlPlatform
    {
        private:
            SdlWindowObPtr m_window_borrowed;

        public:
            SdlPlatform()
            {
                if (!SDL_Init(SDL_INIT_VIDEO)) throw std::runtime_error(SDL_GetError());
                SDL_SetHint(SDL_HINT_MOUSE_TOUCH_EVENTS, "1");
                SDL_SetHint(SDL_HINT_TOUCH_MOUSE_EVENTS, "1");
            }

            ~SdlPlatform()
            {
                SDL_Quit();
            }
            void observeWindow(SdlWindowBrPtr window);
            auto pollEvent() const -> std::optional<Event>;
    };


}

namespace engine::platform
{
    void SdlPlatform::observeWindow(SdlWindowBrPtr window)
    {
        m_window_borrowed = util::observe(&window.get());
    }

    auto SdlPlatform::pollEvent() const -> std::optional<Event>
    {
        SDL_Event event;

        if (!SDL_PollEvent(&event))
        {
            return std::nullopt;
        }

        if (auto* renderer = SDL_GetRenderer(m_window_borrowed.get()))
        {
            if (SDL_ConvertEventToRenderCoordinates(renderer, &event))
            {
                return translateSDLEvent(event);
            }
        }
        return std::nullopt;;
    }
}
