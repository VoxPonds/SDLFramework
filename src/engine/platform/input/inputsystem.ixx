module;
#include "spdlog/spdlog.h"
export module engine.platform.inputsystem;
export import :inputmapping;
export import :inputcontext;
import engine.core.timer;
import engine.core.eventtype;


export namespace engine::platform
{
    /*struct InputConfig {
        std::array<InputMappingContext, static_cast<std::uint8_t>(ContextType::CONTEXT_COUNT)> input_contexts_;
        InputMappingContext gameplay_standard_context_;
    };*/

	template<typename ActionType>
    struct InputSystem 
    {
	    private:
	        std::bitset<static_cast<std::size_t>(EInputCode::KEY_COUNT)> pressed_keys_;
			std::bitset<static_cast<std::size_t>(EInputCode::KEY_COUNT)> down_keys_;
	        std::bitset<static_cast<std::size_t>(EInputCode::KEY_COUNT)> released_keys_;
			std::vector<core::KeyboardEvent> keyboard_events_;

			std::span<const bool> keyboard_state_{};
	        int keyboard_count_{};

	        static bool isValidScancode(EInputCode key)
	        {
    			return static_cast<std::size_t>(key) < static_cast<std::size_t>(EInputCode::KEY_COUNT);
    		}

		public:
	        InputMappingList<ActionType> action_mapping_;

	        uint8_t game_index = 0;

	        explicit InputSystem(InputMappingList<ActionType> mapping_list);

			void beginFrame();

			void endFrame();

			void reset();

	        void processEvent(const core::Event& event);

	        static TriggerType getTriggerType(const core::KeyboardEvent& event);

	        bool getActionEvent(ActionType action)const;

			bool checkKeyDown(EInputCode key) const;

	        bool checkKeyPressed(EInputCode key) const;

	        bool checkKeyReleased(EInputCode key)const;

	        bool matchSequence(const InputSequence& pattern)const;

	        bool checkTrigger(EInputCode key) const;

    };

	template<typename ActionType>
	InputSystem<ActionType>::InputSystem(InputMappingList<ActionType> mapping_list):
		action_mapping_(std::move(mapping_list))
	{

	}

	template<typename ActionType>
	void InputSystem<ActionType>::beginFrame()
    {
    }

	template<typename ActionType>
	void InputSystem<ActionType>::endFrame()
	{
	}

	template<typename ActionType>
	void InputSystem<ActionType>::reset()
	{
		pressed_keys_.reset();
		released_keys_.reset();
		down_keys_.reset();
		keyboard_events_.clear();
		//keyboard_state_ = { SDL_GetKeyboardState(&keyboard_count_), static_cast<size_t>(keyboard_count_) };
	}

	template<typename ActionType>
    void InputSystem<ActionType>::processEvent(const core::Event& event)
    {
		if (std::holds_alternative<core::KeyboardEvent>(event))
		if (const auto* key = std::get_if<core::KeyboardEvent>(&event))
		{
			keyboard_events_.emplace_back(*key);
			switch (key->type)
			{
				case core::EEventType::EVENT_KEY_DOWN:
				{
					if (key->down)
					{
						down_keys_.set(static_cast<std::size_t>(key->scancode));
					}
					else
					{
						pressed_keys_.set(static_cast<std::size_t>(key->scancode));
					}
					break;
				}
				case core::EEventType::EVENT_KEY_UP:
				{
					released_keys_.set(static_cast<std::size_t>(key->scancode));
					break;
				}
				default:
					break;
			}
		}
    }

	template<typename ActionType>
	TriggerType InputSystem<ActionType>::getTriggerType(const core::KeyboardEvent& event)
	{
		switch (event.type)
		{
			case core::EEventType::EVENT_KEY_DOWN:
			{
				if (event.down)
				{
					return TriggerType::TRIGGER_DOWN;
				}
				if (event.pressed)
				{
					return TriggerType::TRIGGER_PRESSED;
				}
				std::unreachable();
			}
			case core::EEventType::EVENT_KEY_UP : return TriggerType::TRIGGER_RELEASED;
			default: std::unreachable();
		}
	}

	template<typename ActionType>
    bool InputSystem<ActionType>::getActionEvent(ActionType action)const
    {
    	auto it = action_mapping_.find(action);
    	if (it == action_mapping_.end()) return false;

    	auto& action_sequence_lists_ = it->second.mapping_lists_;
	    for (auto& pattern : action_sequence_lists_)
	    {
			if (pattern.sequence_.empty()) continue;

			switch (const SingleInputBind& single_bind_ = pattern.sequence_[0]; single_bind_.triggerType)
		    {
			    case TriggerType::TRIGGER_PRESSED:
			    {
				    if (matchSequence(pattern)) return true;
			    	continue;
			    }
		    	case TriggerType::TRIGGER_DOWN:
		    	{
		    		if (checkKeyDown(single_bind_.key)) return true;
		    		continue;
		    	}
			    case TriggerType::TRIGGER_RELEASED:
			    {
				    if (checkKeyReleased(single_bind_.key)) return true;
				    continue;
			    }
			    case TriggerType::TRIGGER_SEQUENCE:
			    {
				    if (matchSequence(pattern)) return true;
				    continue;
			    }
			    default:
			    {
			    	std::unreachable();
				    return false;
			    }
		    }
	    }
	    return false;
    }

	/*template<typename ActionType>
    bool InputSystem<ActionType>::checkKeyBoardState(SDL_Scancode key) const
    {
		if (!isValidScancode(key)) return false;
		return keyboard_state_[key];
    }*/

	template<typename ActionType>
    bool InputSystem<ActionType>::checkKeyPressed(EInputCode key) const
    {
		if (!isValidScancode(key)) return false;
		return pressed_keys_.test(static_cast<std::size_t>(key));
    }

	template<typename ActionType>
	bool InputSystem<ActionType>::checkKeyDown(EInputCode key) const
	{
		if (!isValidScancode(key)) return false;
		return down_keys_.test(static_cast<std::size_t>(key));
	}

	template<typename ActionType>
    bool InputSystem<ActionType>::checkKeyReleased(EInputCode key) const
    {
		if (!isValidScancode(key)) return false;
		return released_keys_.test(static_cast<std::size_t>(key));
    }

	template<typename ActionType>
    bool InputSystem<ActionType>::matchSequence(const InputSequence& pattern)const
    {
	    if (pattern.sequence_.empty()) return false;
		if (pattern.sequenceIndex >= pattern.sequence_.size()) pattern.sequenceIndex = 0;
		/*spdlog::info("---- frame ----");*/
		for (const auto& event : keyboard_events_)
		{
			/*spdlog::info("event key={}, trigger={}, index={}, expected key={}, expected trigger={}",
				static_cast<int>(event.scancode),
				static_cast<int>(getTriggerType(event)),
			pattern.sequenceIndex,
				static_cast<int>(pattern.sequence_[pattern.sequenceIndex].key),
				static_cast<int>(pattern.sequence_[pattern.sequenceIndex].triggerType)
			);*/
			if (event.type != core::EEventType::EVENT_KEY_DOWN)
				continue;
			if (event.down)
				continue;
			const auto now = core::Timer::getTicks();
			// timeout
			if (pattern.lastTriggerTime && now - pattern.lastTriggerTime.value() > pattern.tolerance_ms_)
			{
				pattern.sequenceIndex = 0;
				pattern.lastTriggerTime.reset();
			}
			const auto&[key, triggerType] = pattern.sequence_[pattern.sequenceIndex];
			if (event.scancode != key)
			{
				// not expected
				pattern.sequenceIndex = 0;
				pattern.lastTriggerTime.reset();
				continue;
			}
			/*if (getTriggerType(event) != triggerType)
			{
				// ignore this event
				continue;
			}*/
			// success
			pattern.lastTriggerTime = now;
			++pattern.sequenceIndex;
			// finish
			if (pattern.sequenceIndex == pattern.sequence_.size())
			{
				pattern.sequenceIndex = 0;
				pattern.lastTriggerTime.reset();
				return true;
			}
		}
	    return false;
    }

	template<typename ActionType>
    bool InputSystem<ActionType>::checkTrigger(EInputCode key) const
    {
		if (!isValidScancode(key)) return false;
	    return checkKeyPressed(key) || checkKeyReleased(key) || checkKeyDown(key);
    }

	template<typename ActionType>
	InputSystem(const InputMappingList<ActionType>& mapping_list)->InputSystem<ActionType>;
}
