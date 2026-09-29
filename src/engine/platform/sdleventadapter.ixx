module;
#include "SDL3/SDL_events.h"

export module engine.platform.sdlplatform:sdleventadapter;
import :sdlinputadapter;
import engine.platform.inputcode;
import engine.core.eventtype;
import std;

export namespace engine::platform
{
    inline auto translateSDLEvent(const union SDL_Event& event) -> std::optional<core::Event>;
}

namespace engine::platform
{
    auto translateSDLEvent(const union SDL_Event& event) -> std::optional<core::Event>
    {
        switch (event.type)
        {
            case SDL_EVENT_QUIT:
                return core::QuitEvent{
                .type = core::EEventType::EVENT_QUIT,
                .reserved = event.quit.reserved,
                .timestamp = event.common.timestamp
            };

            case SDL_EVENT_KEY_DOWN:
                return core::KeyboardEvent{
                .type = core::EEventType::EVENT_KEY_DOWN,
                /*.reserved = event.key.reserved,
                .timestamp = event.key.timestamp,
                .windowID = event.key.windowID,
                .which = event.key.which,*/
                .scancode = translateSDLScancode(event.key.scancode),
                .key = event.key.key,
                /*.mod = event.key.mod,
                .raw = event.key.raw,*/
                .pressed = event.key.down,
                .down = event.key.repeat
            };

            case SDL_EVENT_KEY_UP:
                return core::KeyboardEvent{
                .type = core::EEventType::EVENT_KEY_UP,
                /*.reserved = event.key.reserved,
                .timestamp = event.key.timestamp,
                .windowID = event.key.windowID,
                .which = event.key.which,*/
                .scancode = translateSDLScancode(event.key.scancode),
                .key = event.key.key,
                /*.mod = event.key.mod,
                .raw = event.key.raw,*/
                .pressed = event.key.down,
                .down = event.key.repeat
            };
            default:
            {
                return std::nullopt;
            };
        }
        return {};
    }
}