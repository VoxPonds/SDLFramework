module;
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keyboard.h>
#include "SDL3/SDL_timer.h"

export module engine.platform.inputsystem;
export import :inputmapping;
export import :inputcontext;

export namespace engine::platform
{
    struct InputConfig {
        std::array<InputMappingContext, static_cast<uint8_t>(ContextType::CONTEXT_COUNT)> input_contexts_;
        InputMappingContext gameplay_standard_context_;
    };

    struct InputSystem 
    {
	    private:
	        std::bitset<SDL_SCANCODE_COUNT> pressed_keys_;
	        std::bitset<SDL_SCANCODE_COUNT> released_keys_;
	        std::bitset<SDL_SCANCODE_COUNT> repeated_keys_;

			std::span<const bool> keyboard_state_{};
	        int keyboard_count_{};

	        static bool isValidScancode(SDL_Scancode key)
	        {
    			return key >= 0 && static_cast<size_t>(key) < SDL_SCANCODE_COUNT;
    		}

		public:
	        InputConfig input_config_;
	        std::unordered_map<StandardAction, ActionProfile>& action_mapping_ = input_config_.gameplay_standard_context_.actionMapping;

	        uint8_t game_index = 0;

			void beginFrame();

	        void processEvent(const SDL_Event& event);

	        bool getActionEvent(StandardAction action)const;

	        bool checkKeyDown(SDL_Scancode key) const;

	        bool checkKeyPressed(SDL_Scancode key) const;

	        bool checkKeyReleased(SDL_Scancode key)const;

	        bool chordPatternMatch(ChordInputMapping& pattern)const;

	        bool checkKeyPressedRepeat(SDL_Scancode key) const;

	        bool checkTrigger(SDL_Scancode key) const;

    };

    void InputSystem::beginFrame()
    {
	    pressed_keys_.reset();
	    released_keys_.reset();
	    repeated_keys_.reset();
		keyboard_state_ = { SDL_GetKeyboardState(&keyboard_count_), static_cast<size_t>(keyboard_count_) };
    }

    void InputSystem::processEvent(const SDL_Event& event)
    {
	    switch (event.type)
	    {
		    case SDL_EVENT_KEY_DOWN:
			    {
					if (event.key.repeat)
					{
						repeated_keys_.set(event.key.scancode);
					}
					else
					{
						pressed_keys_.set(event.key.scancode);
					}
					break;
			    }
		    case SDL_EVENT_KEY_UP:
			    {
					released_keys_.set(event.key.scancode);
					break;
			    }
		    default:
			    {
					break;
			    }
	    }
    }

    bool InputSystem::getActionEvent(StandardAction action)const
    {
	   // std::vector<ChordInputMapping>& action_chord_lists_ = this->action_mapping_[action].mapping_lists_;
    	auto it = action_mapping_.find(action);
    	if (it == action_mapping_.end())return false;

    	auto& action_chord_lists_ = it->second.mapping_lists_;
	    for (auto& chord_bind_ : action_chord_lists_)
	    //for(const auto& firstMatch : chordbind.input_sequence_)
	    {
			if (chord_bind_.input_sequence_.empty()) continue;

		    const SingleInputBind& single_bind_ = chord_bind_.input_sequence_[0];
		    switch (single_bind_.triggerType)
		    {
			    case TriggerType::TRIGGER_DOWN:
				    {
					    if (checkKeyDown(single_bind_.key)) return true;
					    else continue;
				    }
			    case TriggerType::TRIGGER_PRESSED:
				    {
					    if (chordPatternMatch(chord_bind_)) return true;
					    else continue;
				    }
			    case TriggerType::TRIGGER_RELEASED:
				    {
					    if (checkKeyReleased(single_bind_.key)) return true;
					    else continue;
				    }
			    case TriggerType::TRIGGER_CHORD:
				    {
					    if (chordPatternMatch(chord_bind_)) return true;
					    else continue;
				    }
			    case TriggerType::TRIGGER_PRESSED_REPEAT:
				    {
					    if (checkKeyPressedRepeat(single_bind_.key)) return true;
					    else continue;
				    }
			    default:
				    {
					    return false;
				    }
		    }
	    }
	    return false;
    }

    bool InputSystem::checkKeyDown(SDL_Scancode key) const
    {
    	if (!InputSystem::isValidScancode(key)) return false;
		return keyboard_state_[key];
    }

    bool InputSystem::checkKeyPressed(SDL_Scancode key) const
    {
		return pressed_keys_.test(key);
    }

    bool InputSystem::checkKeyReleased(SDL_Scancode key) const
    {
		return released_keys_.test(key);
    }

    bool InputSystem::chordPatternMatch(ChordInputMapping& pattern)const
    {
	    if (pattern.input_sequence_.empty()) return false;

	    size_t index = pattern.sequenceIndex;
		SDL_Scancode needKey = pattern.input_sequence_[index].key;

	    if (checkKeyPressed(needKey))
	    {
			std::uint64_t now = SDL_GetTicks();
			std::uint64_t diff = now - pattern.lastTriggerTime;
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
			    if (pattern.sequenceIndex == pattern.input_sequence_.size())
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

    bool InputSystem::checkKeyPressedRepeat(SDL_Scancode key) const
    {
		return repeated_keys_.test(key);
    }

    bool InputSystem::checkTrigger(SDL_Scancode key) const
    {
	    return checkKeyPressed(key) || checkKeyReleased(key) || checkKeyDown(key);
    }
}
