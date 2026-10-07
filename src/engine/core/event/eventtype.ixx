module;

export module engine.core.eventtype;
export import :inputeventtype;

import std;

export namespace engine::core
{
    enum class EEventType : std::uint8_t
    {
        EVENT_QUIT,

        EVENT_KEY_DOWN,
        EVENT_KEY_UP,

        EVENT_MOUSE_BUTTON_DOWN,
        EVENT_MOUSE_BUTTON_UP,

        EVENT_FINGER_DOWN,
        EVENT_FINGER_UP,
        EVENT_FINGER_MOTION,
        EVENT_FINGER_CANCELED,
        EVENT_FINGER_FIRST = EVENT_FINGER_DOWN,
        EVENT_FINGER_LAST = EVENT_FINGER_CANCELED,
    };

    struct QuitEvent
    {
        EEventType type;
        std::uint32_t reserved;
        std::uint64_t timestamp;
    };

    using Event = std::variant<
        QuitEvent,
        InputEvent,
        std::monostate
    >;
    using FrothEvent = Event;

}

export using engine::core::Event;
export using engine::core::FrothEvent;