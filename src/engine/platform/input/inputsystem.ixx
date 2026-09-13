module;

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

	        bool getActionEvent(ActionType action);

			bool checkKeyDown(EInputCode key) const;

	        bool checkKeyPressed(EInputCode key) const;

	        bool checkKeyReleased(EInputCode key)const;

	        bool matchSequence(InputSequence& pattern)const;

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
		//keyboard_state_ = { SDL_GetKeyboardState(&keyboard_count_), static_cast<size_t>(keyboard_count_) };
	}

	template<typename ActionType>
    void InputSystem<ActionType>::processEvent(const core::Event& event)
    {
		if (const auto* key = std::get_if<core::KeyboardEvent>(&event))
		{
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
    bool InputSystem<ActionType>::getActionEvent(ActionType action)
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
    bool InputSystem<ActionType>::matchSequence(InputSequence& pattern)const
    {
	    if (pattern.sequence_.empty()) return false;
		if (pattern.sequenceIndex >= pattern.sequence_.size()) pattern.sequenceIndex = 0;
	    size_t index = pattern.sequenceIndex;
		EInputCode needKey = pattern.sequence_[index].key;

	    if (checkKeyPressed(needKey))
	    {
			std::uint64_t now = core::Timer::getTicks();
	    	if (!pattern.lastTriggerTime)
	    	{
	    		pattern.lastTriggerTime = now;
	    	}
			std::uint64_t diff = now - pattern.lastTriggerTime.value();
		    if (diff > pattern.tolerance_ms_)
		    {
			    index = 0;
			    pattern.sequenceIndex = 0;//delete to avoid multiple reset
		    }
		    if (index == 0 || diff <= pattern.tolerance_ms_)
		    {
			    //std::cout << std::format("index:{}\n", pattern.sequenceIndex);
			    pattern.lastTriggerTime = now;
			    pattern.sequenceIndex++;
			    if (pattern.sequenceIndex == pattern.sequence_.size())
			    {
				    pattern.sequenceIndex = 0;
				    return true;
			    }
		    }
		    else
		    {
			    pattern.sequenceIndex = 0;
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
