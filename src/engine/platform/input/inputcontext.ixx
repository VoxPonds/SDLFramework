module;

export module engine.platform.inputsystem:inputcontext;
import :inputmapping;

import engine.platform.inputcode;
import engine.core.math;
import std;

export namespace engine::platform
{
	/*enum class DefaultGameContextType : uint8_t {
		CONTEXT_GAMEPLAY_STANDARD,
		CONTEXT_MENU,
		CONTEXT_PAUSE,
		CONTEXT_COUNT
	};*/

	enum class ContextType : std::uint8_t {
		CONTEXT_COUNT
	};

	struct InputMappingContext
	{
		std::string name;
		std::uint8_t priority = 0;
		bool is_blocking = false;
		bool is_active = true;

		//InputMappingContext() = default;
	};

	struct InputContext
	{
		math::Vector2 m_window_size_;
	};
}
