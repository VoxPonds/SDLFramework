module;

export module engine.platform.inputsystem:inputcontext;
import :inputmapping;
import std.compat;
import engine.platform.inputcode;

export namespace engine::platform
{
	enum class ContextType : uint8_t {
		CONTEXT_GAMEPLAY_STANDARD,
		CONTEXT_MENU,
		CONTEXT_PAUSE,
		CONTEXT_COUNT
	};

	struct InputMappingContext
	{
		std::string name;

		InputMappingList<StandardAction> test_action_mapping
		{
			{
				StandardAction::ACTION_FORWARD,
				{//profile
					{//list
						{
							{//seq
								{EInputCode::KEY_W, TriggerType::TRIGGER_DOWN},
							}
						},
					}, ActionMode::MODE_HOLD
				}
			},
			{
				StandardAction::ACTION_BACKWARD,
				{
					{//profile 
						{//list
							{//seq
								{EInputCode::KEY_S, TriggerType::TRIGGER_DOWN},
							}
						},
					}, ActionMode::MODE_HOLD
				}
			},
			{
				StandardAction::ACTION_LEFT,
				{
					{//profile 
						{//list
							{//seq
								{EInputCode::KEY_A, TriggerType::TRIGGER_DOWN},
							}
						},
					}, ActionMode::MODE_HOLD
				}
			},
			{
				StandardAction::ACTION_RIGHT,
				{
					{//profile 
						{//list
							{//seq
								{EInputCode::KEY_D, TriggerType::TRIGGER_DOWN},
							}
						},
					}, ActionMode::MODE_HOLD
				}
			},
			{
				StandardAction::ACTION_RUN,
				{
					{//profile 
						{//list
							{//seq
								{EInputCode::KEY_LSHIFT, TriggerType::TRIGGER_PRESSED},
							}
						},
					}, ActionMode::MODE_TOGGLE
				}
			},
			{
				StandardAction::ACTION_JUMP,
				{
					{//profile 
						{//list
							{{//seq
								{EInputCode::KEY_SPACE, TriggerType::TRIGGER_DOWN},
							},},
							{{
								{EInputCode::KEY_UNKNOWN, TriggerType::TRIGGER_PRESSED}
							},}
						},
					}, ActionMode::MODE_HOLD
				}
			},
			{
				StandardAction::ACTION_CROUCH,
				{
					{//profile 
						{//list
							{//seq
								{EInputCode::KEY_C, TriggerType::TRIGGER_PRESSED},
							}
						},
					}, ActionMode::MODE_TOGGLE
				}
			},

			//{ StandardAction::ACTION_ATTACK, { {{{ MouseButton::MOUSE_BUTTON_LEFT },TriggerType::TRIGGER_PRESSED},}, } },
			//{ StandardAction::ACTION_INTERACT, { {{{ KEY_F }, TriggerType::TRIGGER_PRESSED},}, } }
		};

		uint8_t priority = 0;
		bool is_blocking = false;
		bool is_active = true;

		//InputMappingContext() = default;

	};
}
