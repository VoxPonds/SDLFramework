module;
#include "SDL3/SDL_render.h"
#include "glm/glm.hpp"
#include "variant"

export module engine.renderer.sdlrenderer;

import engine.platform.sdlwindow;
import engine.platform.sdlptr;
import engine.renderer.renderer;
import engine.renderer.sprite;
import engine.renderer.cameramanager;
import engine.resource.resourcemanager;
import engine.core.math;
import engine.utilities;


export namespace engine::renderer
{
	class SdlRenderer : public Renderer
	{
		private:
			//using SdlRendererPtr = std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>;
			platform::SdlRendererObPtr renderer_ptr{};
			utilities::ObPtr<resource::TextureManager> texture_manager_borrowed;

		public:
			SdlRenderer(const platform::SdlRendererObPtr renderer_borrowed, const utilities::ObPtr<resource::TextureManager> texture_manager_borrowed);
			~SdlRenderer()override = default;

			SdlRenderer(const SdlRenderer&) = delete;
			SdlRenderer& operator=(const SdlRenderer&) = delete;
			SdlRenderer(SdlRenderer&&) = default;
			SdlRenderer& operator=(SdlRenderer&&) = default;

			void renderTest()const;
			std::expected<void, RendererError> renderFrame()override;
			std::expected<void, RendererError> renderFrame(const std::span<const RenderCommand2D>& commands)override;
			void drawTexture(
				const Camera2DManager& camera_manager, const Sprite& sprite, const core::Vector2& position,
				const core::Vector2& scale = { 1.0f, 1.0f }, double angle = 0.0f, SDL_FlipMode flip_mode = SDL_FlipMode::SDL_FLIP_NONE
			)const;
			void drawTexture(const SpriteRenderCommand& command)const;

			platform::SdlRendererObPtr getRendererPtr()const;

			std::expected<void, RendererError> submit(const RenderCommand2D& render_command_2d) override;
			void beginFrame() override;
			void clear() override;
			std::expected<void, RendererError> execute(const RenderCommand2D& render_command_2d)override;
			void present() override;
			void endFrame() override;
			
	};

	SdlRenderer::SdlRenderer(
		const platform::SdlRendererObPtr renderer_borrowed, 
		const utilities::ObPtr<resource::TextureManager> texture_manager_borrowed
	)
	:	renderer_ptr(renderer_borrowed), 
		texture_manager_borrowed(texture_manager_borrowed)
	{

	}

	void SdlRenderer::renderTest() const
	{
		const char* message = "Hello World!";
		int w = 0, h = 0;
		float x, y;
		const float scale = 4.0f;
		SDL_SetRenderLogicalPresentation(getRendererPtr().get(), 1280, 720, SDL_LOGICAL_PRESENTATION_LETTERBOX);
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

	auto SdlRenderer::renderFrame()->std::expected<void, RendererError>
	{
		beginFrame();
		clear();
		for (const auto& command : commands2d_.commands())
		{
			auto state = execute(command);
			if (!state) 
			{
				commands2d_.clear();
				endFrame();
				return std::unexpected(state.error());
			}
		}
		present();
		endFrame();
		commands2d_.clear();

		return {};
	}

	auto SdlRenderer::renderFrame(const std::span<const RenderCommand2D>& commands)->std::expected<void, RendererError>
	{
		beginFrame();
		clear();
		for (const auto& command : commands)
		{
			auto state = execute(command);
			if (!state)
			{
				endFrame();
				return std::unexpected(state.error());
			} 
		}
		present();
		endFrame();

		return {};
	}

	void SdlRenderer::drawTexture(
		const Camera2DManager& camera_manager, const Sprite& sprite, const core::Vector2& position,
		const core::Vector2& scale, double angle, SDL_FlipMode flip_mode
	)const
	{
		auto screen_position = camera_manager.worldToScreen(position);

		// acquire SDL_Texture

		// compute rectangle and call SDL_RenderTextureRotated()
		SDL_RenderTextureRotated(renderer_ptr.get(), platform::TexturePtr{}.get(),
			nullptr, nullptr, angle, nullptr, flip_mode
		);
	}

	void SdlRenderer::drawTexture(const SpriteRenderCommand& command) const
	{
		auto texture = texture_manager_borrowed->getTexture(
			command.sprite.getTextureHandle()
		);
		if (!texture)
		{
			return;
		}
		const auto source_rect = command.sprite.getSourceRect();
		const auto textureSize = resource::TextureManager::getTextureSize(texture.value().get());

		utilities::ObPtr<SDL_FRect> src_rect;
		
		if (source_rect)
		{
			SDL_FRect temp_rect{
					.x = static_cast<float>(source_rect->position.x),
					.y = static_cast<float>(source_rect->position.y),
					.w = static_cast<float>(source_rect->size.x),
					.h = static_cast<float>(source_rect->size.y)
			};
			src_rect = &temp_rect;
		}
		else
		{
			src_rect = nullptr;
		}

		const core::Vector2 source_size =
			source_rect
			? core::Vector2{
				source_rect->size.x,
				source_rect->size.y
			}
			: textureSize.value();

		utilities::ObPtr<SDL_FRect> dst_rect;
		SDL_FRect temp_rect{
			.x = static_cast<float>(command.transform_2d.position.x),
			.y = static_cast<float>(command.transform_2d.position.y),
			.w = static_cast<float>(source_size.x * command.transform_2d.scale.x),
			.h = static_cast<float>(source_size.y * command.transform_2d.scale.y)
		};
		dst_rect = &temp_rect;

		const auto flip_mode = static_cast<SDL_FlipMode>(command.flip_mode);
		if (!SDL_RenderTextureRotated
			(
				renderer_ptr.get(),
				texture.value().get(),
				src_rect.get(),
				dst_rect.get(),
				command.transform_2d.rotation,
				nullptr,
				flip_mode
		))
		{
			std::println(
				"SDL_RenderTextureRotated failed: {}",
				SDL_GetError()
			);
		}
	}

	platform::SdlRendererObPtr SdlRenderer::getRendererPtr()const
	{
		return renderer_ptr;
	}

	void SdlRenderer::beginFrame()
	{
	}

	void SdlRenderer::clear()
	{
		//SDL_SetRenderDrawColor(
		//	renderer_ptr.get(),
		//	0,
		//	0,
		//	0,
		//	255
		//);
		SDL_RenderClear(renderer_ptr.get());
	}
	auto SdlRenderer::submit(const RenderCommand2D& render_command_2d)->std::expected<void, RendererError>
	{
		commands2d_.submit(render_command_2d);
		return std::expected<void, RendererError>(std::in_place);
	}
	auto SdlRenderer::execute(const RenderCommand2D& render_command_2d)->std::expected<void, RendererError>
	{
		std::visit(
		[this]<typename T>(T && command)
			{
				if constexpr (std::is_same_v<std::remove_cvref_t<T>, SpriteRenderCommand>)
				{
					drawTexture(command);
				}
			},
			render_command_2d
		);
		return std::expected<void, RendererError>(std::in_place);
	}

	void SdlRenderer::present()
	{
		SDL_RenderPresent(renderer_ptr.get());
	}

	void SdlRenderer::endFrame()
	{
	}
}

