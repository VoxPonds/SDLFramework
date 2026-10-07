module;

export module engine.core.eventtype:inputeventtype;
import engine.platform.inputcode;
import engine.core.math;
import std;

export namespace engine::core
{
    enum class EEventType : std::uint8_t;

    struct KeyboardEvent
    {
        EEventType type;
        /*std::uint32_t reserved;
        std::uint64_t timestamp;
        std::uint32_t windowID;
        std::uint32_t which;*/
        platform::EKeyCode scancode;
        std::uint32_t key;
        /*std::uint32_t mod;
        std::uint16_t raw;*/
        bool pressed;
        bool down;
    };

    struct MouseButtonEvent
    {
        EEventType type;
        /*std::uint32_t reserved;
        std::uint64_t timestamp;
        std::uint32_t windowID;
        std::uint32_t which;*/
        platform::EMouseButton button;
        bool down;
        std::uint8_t clicks;
        math::Vector2 position;
    };

    struct TouchEvent
    {
        EEventType type;
        /*std::uint32_t reserved;
        std::uint64_t timestamp;
        std::uint32_t windowID;*/
        std::uint64_t touch_id;
        std::uint64_t finger_id;
        float x;
        float y;
        float dx;
        float dy;
        float pressure;
    };

    using InputEvent = std::variant<
            KeyboardEvent,
            MouseButtonEvent,
            /*MouseMotionEvent,
            MouseWheelEvent,*/
            TouchEvent
            /*GamepadButtonEvent,
            GamepadAxisEvent,
            SensorEvent*/
    >;
}

namespace engine::core
{

}
