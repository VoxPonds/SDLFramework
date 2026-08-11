module;
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_video.h"

#include "spdlog/spdlog.h"

export module engine.platform.sdlwindowmanager;
import std.compat;
import engine.platform.sdlptr;

export namespace engine::platform
{
	class SdlWindowManager final
	{
		private:
			//using WindowPtr = std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>;
			WindowPtr window_ptr{};
			explicit SdlWindowManager(WindowPtr window_ptr);
			static std::expected<SdlWindowManager, std::string> create();

		public:
			SdlWindowManager();
			~SdlWindowManager() = default;

			WindowObPtr getWindow() const;

			SdlWindowManager(const SdlWindowManager&) = delete;
			SdlWindowManager& operator=(const SdlWindowManager&) = delete;
			SdlWindowManager(SdlWindowManager&&) = default;
			SdlWindowManager& operator=(SdlWindowManager&&) = delete;

	};

	SdlWindowManager::SdlWindowManager()
	{
		window_ptr = WindowPtr(
			SDL_CreateWindow(
				"Hello World", 
				1280, 
				720, 
				SDL_WINDOW_RESIZABLE)
		);
		if (!window_ptr)
		{
			SDL_Log("Couldn't create window: %s", SDL_GetError());
			auto error = std::string("Failed to create SDL window: ") + SDL_GetError();
			spdlog::error(error);
			throw std::runtime_error(SDL_GetError());
		}
	}

	WindowObPtr SdlWindowManager::getWindow() const
	{
		return window_ptr;
	}

	SdlWindowManager::SdlWindowManager(WindowPtr window_ptr) : window_ptr(std::move(window_ptr))
	{
		
	}

	std::expected<SdlWindowManager, std::string> SdlWindowManager::create()
	{
		auto ptr = WindowPtr(
			SDL_CreateWindow("Hello World", 800, 600, SDL_WINDOW_RESIZABLE)
		);
		if (!ptr)
		{
			//SDL_Log("Couldn't create window: %s", SDL_GetError());
			spdlog::error("Failed to create SDL window");
			return std::unexpected<std::string>("Failed to create SDL window");
		}

		return SdlWindowManager(std::move(ptr));
	}

}




