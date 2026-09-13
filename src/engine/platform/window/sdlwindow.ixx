module;
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_video.h"

export module engine.platform.sdlwindow;
import engine.platform.sdlptr;
import std;

export namespace engine::platform
{
	class SdlWindow final
	{
		private:
			//using WindowPtr = std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>;
			WindowPtr window_ptr{};
			explicit SdlWindow(WindowPtr window_ptr);
			static std::expected<SdlWindow, std::string> create();

		public:
			SdlWindow();
			~SdlWindow() = default;

			WindowObPtr getPtr() const;
			SDL_Window& getRef() const;

			SdlWindow(const SdlWindow&) = delete;
			SdlWindow& operator=(const SdlWindow&) = delete;
			SdlWindow(SdlWindow&&) = default;
			SdlWindow& operator=(SdlWindow&&) = delete;
	};
}

namespace engine::platform
{
	SdlWindow::SdlWindow()
	{
		window_ptr = WindowPtr(
			SDL_CreateWindow(
				"",
				1280,
				720,
				SDL_WINDOW_RESIZABLE)
		);
		if (!window_ptr)
		{
			SDL_Log("Couldn't create window: %s", SDL_GetError());
			auto error = std::string("Failed to create SDL window: ") + SDL_GetError();
			throw std::runtime_error(error);
		}
	}

	SdlWindow::SdlWindow(WindowPtr window_ptr) : window_ptr(std::move(window_ptr))
	{

	}

	WindowObPtr SdlWindow::getPtr() const
	{
		return window_ptr;
	}

	SDL_Window& SdlWindow::getRef() const
	{
		return *window_ptr.get();
	}

	std::expected<SdlWindow, std::string> SdlWindow::create()
	{
		auto ptr = WindowPtr(
			SDL_CreateWindow("Hello World", 800, 600, SDL_WINDOW_RESIZABLE)
		);
		if (!ptr)
		{
			//SDL_Log("Couldn't create window: %s", SDL_GetError());
			return std::unexpected<std::string>("Failed to create SDL window");
		}

		return SdlWindow(std::move(ptr));
	}
}




