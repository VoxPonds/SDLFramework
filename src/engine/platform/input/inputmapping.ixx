module;
#include <initializer_list>

export module engine.platform.inputsystem:inputmapping;
import engine.platform.inputcode;
import std;


export namespace engine::platform
{
    enum class StandardAction : std::uint8_t
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

    enum class TriggerType : std::uint8_t
    {
        TRIGGER_PRESSED,
        TRIGGER_DOWN,
        TRIGGER_RELEASED,
        TRIGGER_SEQUENCE,
        TRIGGER_CHORD,
    };

    enum ActionMode : std::uint8_t
    {
        MODE_HOLD,
        MODE_TOGGLE
    };

    enum class InputDeviceType : std::uint8_t
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
        mutable std::optional<std::uint64_t> lastTriggerTime{ std::nullopt };
        mutable std::size_t sequenceIndex{ 0 };

        InputSequence(const SingleInputBind bind)
            : sequence_{bind}
        {
        }
        InputSequence(const std::initializer_list<SingleInputBind> binds):
            sequence_(binds)
        {
        }
    };

    struct InputSequenceState
    {
        std::optional<std::uint64_t> lastTriggerTime{};
        std::size_t sequenceIndex{0};
    };

    using InputAlternative = std::vector<InputSequence>;
    struct ActionProfile
    {
        InputAlternative mapping_lists_;//x.+x. or x.+y- || a.+a.
        ActionMode actionMode{MODE_HOLD};

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
            return{
                .key {key},
                .triggerType {trigger}
            };
        }

        constexpr auto makeSingleSequence(const EInputCode input, const TriggerType trigger = TriggerType::TRIGGER_PRESSED) -> InputSequence
        {
            return {makeBind(input, trigger)};
        }

        constexpr auto makeSequence(const std::initializer_list<SingleInputBind> inputs) -> InputSequence
        {
            return {inputs};
        }

        constexpr auto pressed(const EInputCode input) -> SingleInputBind
        {
            return makeBind(input, TriggerType::TRIGGER_PRESSED);
        }

        constexpr auto down(const EInputCode input) -> SingleInputBind
        {
            return makeBind(input, TriggerType::TRIGGER_DOWN);
        }

        constexpr auto released(const EInputCode input) -> SingleInputBind
        {
            return makeBind(input, TriggerType::TRIGGER_RELEASED);
        }

        constexpr auto operator>>(const SingleInputBind lhs, const SingleInputBind rhs) -> InputSequence
        {
            return { lhs, rhs };
        }

        constexpr auto operator|(const SingleInputBind lhs, const SingleInputBind rhs) -> InputAlternative
        {
            return { InputSequence{lhs}, InputSequence{rhs} };
        }

        constexpr auto operator|(const InputSequence& lhs, const SingleInputBind rhs) -> InputAlternative
        {
            return { InputSequence{lhs}, InputSequence{rhs} };
        }

        constexpr auto operator|(InputAlternative&& lhs, const SingleInputBind rhs) -> InputAlternative
        {
            lhs.emplace_back(InputSequence{rhs});
            return lhs;
        }

        constexpr auto operator|(InputAlternative&& lhs, const InputSequence rhs) -> InputAlternative
        {
            lhs.emplace_back(rhs);
            return lhs;
        }

        constexpr auto operator|(const InputSequence& lhs, const InputSequence& rhs) -> InputAlternative
        {
            return { InputSequence{lhs}, InputSequence{rhs} };
        }



    }


}
