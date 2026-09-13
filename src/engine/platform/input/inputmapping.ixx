module;

export module engine.platform.inputsystem:inputmapping;
import engine.platform.inputcode;
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
        TRIGGER_PRESSED,
        TRIGGER_DOWN,
        TRIGGER_RELEASED,
        TRIGGER_SEQUENCE,
        TRIGGER_CHORD,
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
        EInputCode key;
        TriggerType triggerType;//x. or x-
    };

    struct InputSequence
    {
        std::vector<SingleInputBind> sequence_;//x.+x. or x.+y.
        std::uint64_t tolerance_ms_ { 250 };
        std::optional<std::uint64_t> lastTriggerTime{ -tolerance_ms_ };
        std::size_t sequenceIndex{ 0 };

    };

    struct ActionProfile
    {
        std::vector<InputSequence> mapping_lists_;//x.+x. or x.+y- || a.+a.
        ActionMode actionMode{ActionMode::MODE_HOLD};
    };

    template<typename Action>
    using InputMappingList = std::unordered_map<Action, ActionProfile>;

    /*template<typename Action>
    class InputMappingList
    {
        private:
            std::unordered_map<Action, ActionProfile> mappings_;

        public:
            InputMappingList(std::initializer_list<std::pair<Action, InputSequence>> mappings)
            {
                for (auto&& [action, sequence] : mappings)
                {
                    mappings_.emplace(
                        action,
                        ActionProfile{sequence}
                    );
                }
            }
    };*/

    namespace input
    {
        constexpr auto makeBind(const EInputCode key, const TriggerType trigger) -> SingleInputBind
        {
            return
            SingleInputBind{
                .key = key,
                .triggerType = trigger
            };
        }
        constexpr auto makeSingleSequence(const EInputCode input, const TriggerType trigger = TriggerType::TRIGGER_PRESSED) -> InputSequence
        {
            return InputSequence{
                .sequence_ = {
                    makeBind(input, trigger)
                }
            };
        }
        constexpr auto makeSequence(const std::initializer_list<SingleInputBind> inputs) -> InputSequence
        {
            return InputSequence{
                .sequence_ = inputs
            };
        }

        constexpr auto pressed(const EInputCode input) -> InputSequence
        {
            return makeSingleSequence(input, TriggerType::TRIGGER_PRESSED);
        }
        constexpr auto down(const EInputCode input) -> InputSequence
        {
            return makeSingleSequence(input, TriggerType::TRIGGER_DOWN);
        }
        constexpr auto released(const EInputCode input) -> InputSequence
        {
            return makeSingleSequence(input, TriggerType::TRIGGER_RELEASED);
        }
    }


}
