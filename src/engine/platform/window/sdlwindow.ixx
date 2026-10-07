module;
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_video.h"

export module engine.platform.sdlwindow;
import engine.platform.sdlptr;
import engine.core.appconfig;
import engine.core.math;
import std;

export namespace engine::platform
{
	class SdlWindow final
	{
		private:
			SdlWindowPtr window_ptr{};
			explicit SdlWindow(SdlWindowPtr window_ptr);
			static std::expected<SdlWindow, std::string> create();

		public:
			SdlWindow(int width, int height, const std::string_view title, std::uint64_t flags);
			explicit SdlWindow(const core::WindowConfig &config);
			~SdlWindow() = default;

			SdlWindowObPtr getPtr() const;
			SDL_Window& getRef() const;

			auto getWindowSize() const -> math::Vector2;

			static auto getWindowSizeFromID(SDL_WindowID id) -> math::Vector2;

			SdlWindow(const SdlWindow&) = delete;
			SdlWindow& operator=(const SdlWindow&) = delete;
			SdlWindow(SdlWindow&&) = default;
			SdlWindow& operator=(SdlWindow&&) = delete;
	};
}

namespace engine::platform
{
	SdlWindow::SdlWindow(const int width, const int height,
		const std::string_view title, const std::uint64_t flags)
	{
		/*window_ptr = WindowPtr(SDL_CreateWindow("",1280,720,SDL_WINDOW_RESIZABLE));*/
		window_ptr = SdlWindowPtr(
			SDL_CreateWindow(
				title.data(),
				width,
				height,
				flags)
		);
		if (!window_ptr)
		{
			SDL_Log("Couldn't create window: %s", SDL_GetError());
			auto error = std::string("Failed to create SDL window: ") + SDL_GetError();
			throw std::runtime_error(error);
		}
	}

	SdlWindow::SdlWindow(const core::WindowConfig& config)
	{
		window_ptr = SdlWindowPtr(
			SDL_CreateWindow(
				config.title.data(),
				config.width,
				config.height,
				config.flags)
		);
		if (!window_ptr)
		{
			SDL_Log("Couldn't create window: %s", SDL_GetError());
			auto error = std::string("Failed to create SDL window: ") + SDL_GetError();
			throw std::runtime_error(error);
		}
	}

	SdlWindow::SdlWindow(SdlWindowPtr window_ptr) : window_ptr(std::move(window_ptr))
	{

	}

	SdlWindowObPtr SdlWindow::getPtr() const
	{
		return SdlWindowObPtr(window_ptr);
	}

	SDL_Window& SdlWindow::getRef() const
	{
		return *window_ptr.get();
	}

	auto SdlWindow::getWindowSize() const -> math::Vector2
	{
		int width{};
		int height{};

		SDL_GetWindowSize(window_ptr.get(), &width, &height);

		return {width, height};
	}

	auto SdlWindow::getWindowSizeFromID(SDL_WindowID id) -> math::Vector2
	{
		int width{};
		int height{};

		if (SDL_Window* window = SDL_GetWindowFromID(id))
		{
			SDL_GetWindowSize(window, &width, &height);
		}
		return {width, height};
	}

	std::expected<SdlWindow, std::string> SdlWindow::create()
	{
		auto ptr = SdlWindowPtr(
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




