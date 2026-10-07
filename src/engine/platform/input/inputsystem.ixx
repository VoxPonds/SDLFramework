module;

export module engine.platform.inputsystem;
export import :inputmapping;
export import :inputcontext;

import engine.core.appconfig;
import engine.core.timer;
import engine.core.eventtype;
import engine.core.math;

export namespace engine::platform
{
    /*struct InputConfig {
        std::array<InputMappingContext, static_cast<std::uint8_t>(ContextType::CONTEXT_COUNT)> input_contexts_;
        InputMappingContext gameplay_standard_context_;
    };*/

	template<typename T>
	concept EnumAction = std::is_enum_v<T>;

	template<typename T>
	concept HasAction = EnumAction<T>;

	template<typename T>
	concept MonoAction = std::same_as<T, std::monostate>;

	template<typename T>
	concept InputActionType = MonoAction<T> || HasAction<T>;

	struct ClickInfo
	{
		math::Vector2 position;
	};

	template<typename ActionType = std::monostate> requires InputActionType<ActionType>
    struct InputSystem
	{
		using MappingListType = InputMappingList<ActionType>;

		private:
			math::Vector2 m_window_size_;
			std::bitset<static_cast<std::size_t>(EInputCode::COUNT)> m_pressed_inputs_;
			std::bitset<static_cast<std::size_t>(EInputCode::COUNT)> m_down_inputs_;
			std::bitset<static_cast<std::size_t>(EInputCode::COUNT)> m_released_inputs_;

			std::vector<core::KeyboardEvent> m_keyboard_events_;
			std::vector<core::MouseButtonEvent> m_mouse_events_;

			std::span<const bool> m_keyboard_state_{};

			int m_keyboard_count_{};

			static bool isValidCode(const ButtonInput button)
			{
				return static_cast<std::size_t>(button.value) < static_cast<std::size_t>(EInputCode::COUNT);
			}

		public:
			InputMappingList<ActionType> action_mapping_;

			std::uint8_t game_index = 0;

			InputSystem() requires HasAction<ActionType> = delete;

			explicit InputSystem(InputMappingList<ActionType> mapping_list, const core::AppConfig& config) requires HasAction<ActionType>;

			explicit InputSystem(const core::AppConfig& config, InputMappingList<ActionType> mapping_list) requires HasAction<ActionType>;

			explicit InputSystem(const core::AppConfig& config) requires MonoAction<ActionType>;

			void run(const core::Event& event);

			void beginFrame();

			void endFrame();

			void reset();

			void injectEvent(const core::Event& event);

			void processEvent(const core::Event& event);

			void processInputEvent(const core::InputEvent& event);

			static TriggerType getTriggerType(const core::KeyboardEvent& event);

			bool getAction(ActionType action) const requires HasAction<ActionType>;

			auto getClick(EMouseButton button) const -> std::optional<ClickInfo>;

			auto getClicks(EMouseButton button) const -> std::span<const ClickInfo>;

		private:
			bool checkPressed(ButtonInput button) const;

			bool checkDown(ButtonInput button) const;

			bool checkReleased(ButtonInput button) const;

			bool matchSequence(const InputSequence& pattern) const;

			bool checkTouchGesture(ETouchGesture gesture) const;

			bool checkClick(EClickRegion region) const;

			bool checkTrigger(ButtonInput button) const;

			void processInputEvent(const core::KeyboardEvent& event);

			void processInputEvent(const core::MouseButtonEvent& event);

			void processInputEvent(const core::TouchEvent& event);
	};

	template<typename ActionType> requires InputActionType<ActionType>
	InputSystem<ActionType>::InputSystem(const core::AppConfig &config) requires MonoAction<ActionType>:
		m_window_size_{config.window_config_.width, config.window_config_.height}
	{
	}

	template<typename ActionType> requires InputActionType<ActionType>
	InputSystem<ActionType>::InputSystem(InputMappingList<ActionType> mapping_list, const core::AppConfig& config) requires HasAction<ActionType>:
		m_window_size_{config.window_config_.width, config.window_config_.height},
		action_mapping_(std::move(mapping_list))
	{
	}

	template<typename ActionType> requires InputActionType<ActionType>
	InputSystem<ActionType>::InputSystem(const core::AppConfig &config, InputMappingList<ActionType> mapping_list) requires HasAction<ActionType>:
		m_window_size_{config.window_config_.width, config.window_config_.height},
		action_mapping_(std::move(mapping_list))
	{
	}

	template<typename ActionType> requires InputActionType<ActionType>
	InputSystem(const core::AppConfig&, InputMappingList<ActionType>) -> InputSystem<ActionType>;

	template<typename ActionType> requires InputActionType<ActionType>
	void InputSystem<ActionType>::run(const core::Event &event)
	{
		beginFrame();
		processEvent(event);
		endFrame();
		reset();
	}

	template<typename ActionType> requires InputActionType<ActionType>
	void InputSystem<ActionType>::beginFrame()
    {

    }

	template<typename ActionType> requires InputActionType<ActionType>
	void InputSystem<ActionType>::endFrame()
	{
	}

	template<typename ActionType> requires InputActionType<ActionType>
	void InputSystem<ActionType>::reset()
	{
		m_pressed_inputs_.reset();
		m_released_inputs_.reset();
		m_down_inputs_.reset();
		m_keyboard_events_.clear();
		m_mouse_events_.clear();
		//keyboard_state_ = { SDL_GetKeyboardState(&keyboard_count_), static_cast<size_t>(keyboard_count_) };
	}

	template<typename ActionType> requires InputActionType<ActionType>
	void InputSystem<ActionType>::injectEvent(const core::Event &event)
	{
		processEvent(event);
	}

	template<typename ActionType> requires InputActionType<ActionType>
    void InputSystem<ActionType>::processEvent(const Event& event)
    {
		if (const auto* input_events = std::get_if<core::InputEvent>(&event))
		{
			processInputEvent(*input_events);
		}
    }

	template<typename ActionType> requires InputActionType<ActionType>
	void InputSystem<ActionType>::processInputEvent(const core::InputEvent& event)
	{
		std::visit(
			[this](const auto& input_event)
			{
			   processInputEvent(input_event);
			},
			event
		);
	}

	template<typename ActionType> requires InputActionType<ActionType>
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

	template<typename ActionType> requires InputActionType<ActionType>
    bool InputSystem<ActionType>::getAction(ActionType action) const requires HasAction<ActionType>
    {
    	auto it = action_mapping_.find(action);
    	if (it == action_mapping_.end()) return false;

	    for (auto& action_sequence_lists_ = it->second.mapping_lists_;
	    	auto& pattern : action_sequence_lists_)
	    {
	    	if (std::holds_alternative<TouchGestureBind>(pattern))
	    	{
	    		const auto& gesture = std::get<TouchGestureBind>(pattern);
	    		if (checkTouchGesture(gesture.gesture)) return true;
	    		continue;
	    	}

	    	const auto& button_pattern = std::get<InputSequence>(pattern);
	    	if (button_pattern.sequence_.empty()) continue;

	    	const auto& single_bind_ =  button_pattern.sequence_.front();

	    	if (button_pattern.sequence_.size() > 1)
	    	{
	    		if (std::holds_alternative<ButtonBind>(single_bind_))
	    		if (matchSequence(button_pattern)) return true;
	    		continue;
	    	}

	    	if (const auto* click_bind = std::get_if<ClickBind>(&single_bind_))
	    	{
	    		if (checkClick(click_bind->region)) return true;
		    }

	    	else if (const auto* button_bind = std::get_if<ButtonBind>(&single_bind_))
			switch (button_bind->triggerType)
		    {
			    case TriggerType::TRIGGER_PRESSED:
			    {
				    if (checkPressed(button_bind->button)) return true;
			    	continue;
			    }
		    	case TriggerType::TRIGGER_DOWN:
		    	{
				    if (checkDown(button_bind->button)) return true;
		    		continue;
		    	}
			    case TriggerType::TRIGGER_RELEASED:
			    {
			    	if (checkReleased(button_bind->button)) return true;
				    continue;
			    }
			    case TriggerType::TRIGGER_SEQUENCE:
			    {
				    if (matchSequence(button_pattern)) return true;
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

	template<typename ActionType> requires InputActionType<ActionType>
	auto InputSystem<ActionType>::getClick(const EMouseButton button) const -> std::optional<ClickInfo>
	{
		const auto result = std::ranges::find_if(
			m_mouse_events_,
			[button](const core::MouseButtonEvent& event) -> bool
			{
				return event.down && event.button == button ;
			}
		);

		if (result == m_mouse_events_.end())
		{
			return std::nullopt;
		}

		return ClickInfo{
			.position = {result->position}
		};
	}

	template<typename ActionType> requires InputActionType<ActionType>
	auto InputSystem<ActionType>::getClicks(EMouseButton button) const -> std::span<const ClickInfo>
	{
		return {};
	}

	/*template<typename ActionType>
    bool InputSystem<ActionType>::checkKeyBoardState(SDL_Scancode key) const
    {
		if (!isValidScancode(key)) return false;
		return keyboard_state_[key];
    }*/

	template<typename ActionType> requires InputActionType<ActionType>
    bool InputSystem<ActionType>::checkPressed(const ButtonInput button) const
    {
		if (!isValidCode(button)) return false;
		return m_pressed_inputs_.test(static_cast<std::size_t>(button.value));
    }

	template<typename ActionType> requires InputActionType<ActionType>
	bool InputSystem<ActionType>::checkDown(const ButtonInput button) const
	{
		if (!isValidCode(button)) return false;
		return m_down_inputs_.test(static_cast<std::size_t>(button.value));
	}

	template<typename ActionType> requires InputActionType<ActionType>
    bool InputSystem<ActionType>::checkReleased(ButtonInput button) const
    {
		if (!isValidCode(button)) return false;
		return m_released_inputs_.test(static_cast<std::size_t>(button.value));
    }

	template<typename ActionType> requires InputActionType<ActionType>
    bool InputSystem<ActionType>::matchSequence(const InputSequence& pattern)const
    {
	    if (pattern.sequence_.empty()) return false;
		if (pattern.sequenceIndex >= pattern.sequence_.size()) pattern.sequenceIndex = 0;

		for (const auto& event : m_keyboard_events_)
		{
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
			const auto& single_bind = pattern.sequence_[pattern.sequenceIndex];
			if (!std::holds_alternative<ButtonBind>(single_bind)) return false;
			const auto& [button, triggerType] = std::get<ButtonBind>(single_bind);
			if (event.scancode != fromUnderlying<EKeyCode>(button.value))
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

	template<typename ActionType> requires InputActionType<ActionType>
	bool InputSystem<ActionType>::checkTouchGesture(ETouchGesture gesture) const
	{
		//return recognized_gestures_.contains(gesture);
		return {};
	}

	template<typename ActionType> requires InputActionType<ActionType>
	bool InputSystem<ActionType>::checkClick(EClickRegion region) const
	{
		return std::ranges::any_of(
			m_mouse_events_,
			[this, region](const core::MouseButtonEvent& event) -> bool
			{
				if (event.type != core::EEventType::EVENT_MOUSE_BUTTON_DOWN) return false;

				const float normalize_x = event.position.x / m_window_size_.x;
				const float normalize_y = event.position.y / m_window_size_.y;

				const float dx = normalize_x - 0.5f;
				const float dy = normalize_y - 0.5f;

				switch (region)
				{
					case EClickRegion::SCREEN_TOP : return dy < 0.0f && std::abs(dy) >= std::abs(dx);
					case EClickRegion::SCREEN_BOTTOM : return dy >= 0.0f && std::abs(dy) >= std::abs(dx);
					case EClickRegion::SCREEN_LEFT : return dx < 0.0f && std::abs(dx) > std::abs(dy);
					case EClickRegion::SCREEN_RIGHT : return dx >= 0.0f && std::abs(dx) > std::abs(dy);
					default : return false;
				}
			}
		);
	}


	template<typename ActionType> requires InputActionType<ActionType>
    bool InputSystem<ActionType>::checkTrigger(const ButtonInput button) const
    {
		if (!isValidCode(button)) return false;
	    return checkPressed(button) || checkReleased(button) || checkDown(button);
    }

	template<typename ActionType> requires InputActionType<ActionType>
	void InputSystem<ActionType>::processInputEvent(const core::KeyboardEvent& event)
	{
		m_keyboard_events_.emplace_back(event);
		switch (event.type)
		{
			case core::EEventType::EVENT_KEY_DOWN:
			{
				if (event.down)
				{
					m_down_inputs_.set(static_cast<std::size_t>(event.scancode));
				}
				else
				{
					m_pressed_inputs_.set(static_cast<std::size_t>(event.scancode));
				}
				break;
			}
			case core::EEventType::EVENT_KEY_UP:
			{
				m_released_inputs_.set(static_cast<std::size_t>(event.scancode));
				break;
			}
			default:
				break;
		}
	}

	template<typename ActionType> requires InputActionType<ActionType>
	void InputSystem<ActionType>::processInputEvent(const core::MouseButtonEvent& event)
	{
		m_mouse_events_.emplace_back(event);
		switch (event.type)
		{
			case core::EEventType::EVENT_MOUSE_BUTTON_DOWN:
			{
				//std::println("get mouse button down event");
				m_pressed_inputs_.set(static_cast<std::size_t>(event.button));
				break;
			}
			case core::EEventType::EVENT_MOUSE_BUTTON_UP:
			{
				//std::println("get mouse button up event");
				m_released_inputs_.set(static_cast<std::size_t>(event.button));
				break;
			}
			default:
				break;
		}
		//injectEvent(core::TouchEvent{.type = core::EEventType::EVENT_FINGER_DOWN});
	}

	template<typename ActionType> requires InputActionType<ActionType>
	void InputSystem<ActionType>::processInputEvent(const core::TouchEvent& event)
	{

		switch (event.type)
		{
			case core::EEventType::EVENT_FINGER_DOWN:
			{
				//std::println("get finger down event");
				//m_pressed_inputs_.set(static_cast<std::size_t>(event.button));
				break;
			}
			case core::EEventType::EVENT_FINGER_UP:
			{
				//m_released_inputs_.set(static_cast<std::size_t>(event.button));
				break;
			}
			default:
				break;
		}
	}

	template<typename ActionType>
	InputSystem(const InputMappingList<ActionType>& mapping_list)->InputSystem<ActionType>;

	using DefaultInputSystem = InputSystem<>;
}
