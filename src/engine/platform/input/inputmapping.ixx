module;

export module engine.platform.inputsystem:inputmapping;
import engine.platform.inputcode;

import std;

export namespace engine::platform
{
    enum class TriggerType : std::uint8_t
    {
        TRIGGER_PRESSED,
        TRIGGER_DOWN,
        TRIGGER_RELEASED,
        TRIGGER_SEQUENCE,
        TRIGGER_CHORD,
    };

    enum class ActionMode : std::uint8_t
    {
        MODE_HOLD,
        MODE_TOGGLE
    };

    enum class InputSourceType : std::uint8_t
    {
        SOURCE_KEYBOARD,
        SOURCE_MOUSE,
        SOURCE_TOUCH,
        SOURCE_GAMEPAD,
        SOURCE_SENSOR,
        SOURCE_COUNT,
    };

    struct ButtonBind
    {
        ButtonInput button {};
        TriggerType triggerType {};//x. or x-
    };

    struct TouchGestureBind
    {
        ETouchGesture gesture {};
    };

    struct ClickBind
    {
        EClickRegion region {};
    };

    using SingleInputBind = std::variant<ButtonBind, ClickBind>;

    struct InputSequence
    {
        std::vector<SingleInputBind> sequence_ {};//x.+x. or x.+y.
        std::uint64_t tolerance_ms_ { 250 };
        mutable std::optional<std::uint64_t> lastTriggerTime { std::nullopt };
        mutable std::size_t sequenceIndex { 0 };

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

    using ActionBind = std::variant<InputSequence, TouchGestureBind>;
    using InputAlternative = std::vector<ActionBind>;

    struct ActionProfile
    {
        InputAlternative mapping_lists_;//x.+x. or x.+y- || a.+a.
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
        constexpr auto makeBind(const ButtonInput button, const TriggerType trigger) -> SingleInputBind
        {
            return ButtonBind{
                .button {button},
                .triggerType {trigger}
            };
        }

        constexpr auto makeSingleSequence(const ButtonInput input, const TriggerType trigger = TriggerType::TRIGGER_PRESSED) -> InputSequence
        {
            return {makeBind(input, trigger)};
        }

        constexpr auto makeSequence(const std::initializer_list<SingleInputBind> inputs) -> InputSequence
        {
            return {inputs};
        }

        template<IsButton E>
        constexpr auto pressed(const E input) -> SingleInputBind
        {
            return makeBind({std::to_underlying(input)}, TriggerType::TRIGGER_PRESSED);
        }

        template<IsButton E>
        constexpr auto down(const E input) -> SingleInputBind
        {
            return makeBind({std::to_underlying(input)}, TriggerType::TRIGGER_DOWN);
        }

        template<IsButton E>
        constexpr auto released(const E input) -> SingleInputBind
        {
            return makeBind({std::to_underlying(input)}, TriggerType::TRIGGER_RELEASED);
        }

        constexpr auto click(const EClickRegion region) -> SingleInputBind
        {
            return ClickBind{region};
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

        constexpr auto operator|(InputAlternative&& lhs, const InputSequence& rhs) -> InputAlternative
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
