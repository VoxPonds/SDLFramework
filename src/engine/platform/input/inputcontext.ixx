module;
#include "SDL3/SDL_scancode.h"

export module engine.platform.inputsystem:inputcontext;
import std.compat;
import :inputmapping;

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

		std::unordered_map<StandardAction, ActionProfile> actionMapping
		{
			{
				StandardAction::ACTION_FORWARD,
				{
					{//profile 
						{//list
							{//seq
								{SDL_SCANCODE_W, TriggerType::TRIGGER_DOWN},
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
								{SDL_SCANCODE_S, TriggerType::TRIGGER_DOWN},
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
								{SDL_SCANCODE_A, TriggerType::TRIGGER_DOWN},
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
								{SDL_SCANCODE_D, TriggerType::TRIGGER_DOWN},
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
								{SDL_SCANCODE_LSHIFT, TriggerType::TRIGGER_PRESSED},
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
								{SDL_SCANCODE_SPACE, TriggerType::TRIGGER_DOWN},
							},},
							{{
								{SDL_SCANCODE_UNKNOWN, TriggerType::TRIGGER_PRESSED}
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
								{SDL_SCANCODE_C, TriggerType::TRIGGER_PRESSED},
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
