module;
#include "SDL3/SDL_scancode.h"

export module engine.platform.inputsystem:inputmapping;
import std.compat;

export namespace engine::platform
{
    enum class StandardAction : uint8_t
    {
        ACTION_FORWARD,
        ACTION_LEFT,
        ACTION_RIGHT,
        ACTION_BACKWARD,
        ACTION_RUN,
        ACTION_JUMP,
        ACTION_CROUCH,
        ACTION_ATTACK,
        ACTION_INTERACT,
    };

    enum class TriggerType : uint8_t
    {
        TRIGGER_DOWN,
        TRIGGER_PRESSED,
        TRIGGER_RELEASED,
        TRIGGER_CHORD,
        TRIGGER_PRESSED_REPEAT
    };

    enum ActionMode : uint8_t
    {
        MODE_HOLD,
        MODE_TOGGLE
    };

    enum class InputDeviceType : uint8_t
    {
        DEVICE_PC,
        DEVICE_GAMEPAD,
        DEVICE_MOBILE,
        DEVICE_COUNT,
    };
    struct SingleInputBind
    {
        SDL_Scancode key;
        TriggerType triggerType;//x. or x-
    };

    struct ChordInputMapping
    {
        std::vector<SingleInputBind> input_sequence_;//x.+x. or x.+y.
        double tolerance = 0.25;          
    	double lastTriggerTime = -tolerance;
        size_t sequenceIndex = 0;
    };

    struct ActionProfile
    {
        std::vector<ChordInputMapping> mapping_lists_;//x.+x. or x.+y- || a.+a.
        ActionMode actionMode = ActionMode::MODE_HOLD;
    };
}
