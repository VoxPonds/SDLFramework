module;
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_render.h"
#include "spdlog/spdlog.h"
#include "glm/glm.hpp"

export module engine.renderer.sdlrenderer;
import engine.platform.sdlwindowmanager;
import std.compat;
import engine.platform.sdlptr;
import engine.core.math;
import engine.renderer.cameramanager;
import engine.renderer.sprite;

export namespace engine::renderer
{
	class SdlRenderer final
	{
		private:
			//using RendererPtr = std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>;
			platform::RendererPtr renderer_ptr{};

		public:
			SdlRenderer(const platform::SdlWindowManager& sdl_window_manager);
			~SdlRenderer() = default;

			SdlRenderer(const SdlRenderer&) = delete;
			SdlRenderer& operator=(const SdlRenderer&) = delete;
			SdlRenderer(SdlRenderer&&) = default;
			SdlRenderer& operator=(SdlRenderer&&) = default;

			void renderTest()const;

			void drawSprite(const Camera2DManager& camera_manager, const Sprite& sprite, const core::Vector2& position,
				const core::Vector2& scale = { 1.0f, 1.0f }, double angle = 0.0f, SDL_FlipMode flip_mode = SDL_FlipMode::SDL_FLIP_NONE
			);

			platform::RendererObPtr getSDLRendererRef()const;

			void clear()const;

			void present()const;
	};

	SdlRenderer::SdlRenderer(const platform::SdlWindowManager& sdl_window_manager)
	{
		//renderer_ptr = RendererPtr(SDL_CreateRenderer(&sdlwindow.getWindow(), nullptr), SDL_DestroyRenderer);
		renderer_ptr = platform::RendererPtr(SDL_CreateRenderer(sdl_window_manager.getWindow().get(), nullptr));
		if (!renderer_ptr) 
		{
			auto error = std::string("Failed to create SDL renderer: ") + SDL_GetError();
			spdlog::error(error);
			throw std::runtime_error(SDL_GetError());
		}
	}

	void SdlRenderer::renderTest() const
	{
		const char* message = "Hello World!";
		int w = 0, h = 0;
		float x, y;
		const float scale = 4.0f;
		SDL_SetRenderLogicalPresentation(getSDLRendererRef().get(), 1280, 720, SDL_LOGICAL_PRESENTATION_LETTERBOX);
		/* Center the message and scale it up */
		SDL_GetRenderOutputSize(renderer_ptr.get(), &w, &h);
		SDL_SetRenderScale(renderer_ptr.get(), scale, scale);
		x = ((w / scale) - SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE * SDL_strlen(message)) / 2;
		y = ((h / scale) - SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE) / 2;

		/* Draw the message */
		SDL_SetRenderDrawColor(renderer_ptr.get(), 0, 0, 0, 255);
		SDL_RenderClear(renderer_ptr.get());
		SDL_SetRenderDrawColor(renderer_ptr.get(), 255, 255, 255, 255);
		SDL_RenderDebugText(renderer_ptr.get(), x, y, message);
		SDL_RenderPresent(renderer_ptr.get());

	}

	void SdlRenderer::drawSprite(const Camera2DManager& camera_manager, const Sprite& sprite, const core::Vector2& position,
		const core::Vector2& scale, double angle, SDL_FlipMode flip_mode)
	{
		auto screen_position = camera_manager.worldToScreen(position);

		// acquire SDL_Texture

		// compute rectangle and call SDL_RenderTextureRotated()
		SDL_RenderTextureRotated(renderer_ptr.get(), platform::TexturePtr{}.get(), 
			nullptr, nullptr, angle, nullptr, flip_mode
		);
	}

	platform::RendererObPtr SdlRenderer::getSDLRendererRef()const
	{
		return renderer_ptr;
	}

	void SdlRenderer::clear()const
	{
		SDL_SetRenderDrawColor(
			renderer_ptr.get(),
			0,
			0,
			0,
			255
		);
		SDL_RenderClear(renderer_ptr.get());
	}

	void SdlRenderer::present()const
	{
		SDL_RenderPresent(renderer_ptr.get());
	}


}

