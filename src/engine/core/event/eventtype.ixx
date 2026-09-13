module;

export module engine.core.eventtype;
import engine.platform.inputcode;
import std;

export namespace engine::core
{
    enum class EEventType : std::uint8_t
    {
        EVENT_QUIT,

        EVENT_KEY_DOWN,
        EVENT_KEY_UP,
    };

    struct KeyboardEvent
    {
        EEventType type;
        /*std::uint32_t reserved;
        std::uint64_t timestamp;
        std::uint32_t windowID;
        std::uint32_t which;*/
        platform::EInputCode scancode;
        std::uint32_t key;
        /*std::uint32_t mod;
        std::uint16_t raw;*/
        bool pressed;
        bool down;
    };

    struct QuitEvent
    {
        EEventType type;
        std::uint32_t reserved;
        std::uint64_t timestamp;
    };

    using Event = std::variant<
        KeyboardEvent,
        QuitEvent
    >;
}
