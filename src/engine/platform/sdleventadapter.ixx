module;
#include "SDL3/SDL_events.h"

export module engine.platform.sdlplatform:sdleventadapter;
import :sdlinputadapter;
import engine.platform.inputcode;
import engine.core.eventtype;
import engine.core.math;
import std;

export namespace engine::platform
{
    inline auto translateSDLEvent(const union SDL_Event& event) -> std::optional<Event>;
}

namespace engine::platform
{
    auto translateSDLEvent(const union SDL_Event& event) -> std::optional<Event>
    {
        switch (event.type)
        {
            case SDL_EVENT_QUIT:{}
                return core::QuitEvent{
                    .type = core::EEventType::EVENT_QUIT,
                    .reserved = event.quit.reserved,
                    .timestamp = event.common.timestamp
                };

            case SDL_EVENT_KEY_DOWN:
            case SDL_EVENT_KEY_UP:
                return core::KeyboardEvent{
                    .type = event.type == SDL_EVENT_KEY_DOWN
                        ? core::EEventType::EVENT_KEY_DOWN
                        : core::EEventType::EVENT_KEY_UP,
                    .scancode = translateSDLScancode(event.key.scancode),
                    .key = event.key.key,
                    .pressed = event.key.down,
                    .down = event.key.repeat
                };

            case SDL_EVENT_MOUSE_BUTTON_DOWN:
            case SDL_EVENT_MOUSE_BUTTON_UP:
                return core::MouseButtonEvent{
                    .type = event.type == SDL_EVENT_MOUSE_BUTTON_DOWN
                        ? core::EEventType::EVENT_MOUSE_BUTTON_DOWN
                        : core::EEventType::EVENT_MOUSE_BUTTON_UP,
                    .button = translateSDLMouseButton(event.button.button),
                    .down = event.button.down,
                    .clicks = event.button.clicks,
                    .position = { event.button.x, event.button.y }
                };

            case SDL_EVENT_FINGER_DOWN:
            case SDL_EVENT_FINGER_UP:
                return core::TouchEvent{
                    .type = event.type == SDL_EVENT_FINGER_DOWN
                        ? core::EEventType::EVENT_FINGER_DOWN
                        : core::EEventType::EVENT_FINGER_UP,
                    .touch_id = event.tfinger.touchID,
                    .finger_id = event.tfinger.fingerID,
                    .x = std::clamp(event.tfinger.x, 0.0f, 1.0f),
                    .y = std::clamp(event.tfinger.y, 0.0f, 1.0f),
                    .dx = std::clamp(event.tfinger.dx, -1.0f, 1.0f),
                    .dy = std::clamp(event.tfinger.dy, -1.0f, 1.0f),
                    .pressure = std::clamp(event.tfinger.pressure, 0.0f, 1.0f)
                };

            default:
            {
                return std::nullopt;
            };
        }
        return {};
    }


}