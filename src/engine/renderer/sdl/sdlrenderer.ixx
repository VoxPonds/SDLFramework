module;
#include "SDL3/SDL_render.h"
#include "glm/glm.hpp"
#include "variant"

export module engine.render.sdlrenderer;

import engine.platform.sdlwindow;
import engine.platform.sdlptr;
import engine.render.rendererbackend;
import engine.render.sprite;
import engine.render.framerecorder;
import engine.render.cameramanager;
import engine.render.framedata;
import engine.render.sdlrenderdevice;
import engine.render.sdlrendereradapter;
import engine.render.texturemanager;
import engine.resource.resourcemanager;
import engine.core.math;
import engine.utilities;


export namespace engine::render
{
	class SdlRenderer : public IRendererBackend
	{
		private:
			//using SdlRendererDevicePtr = std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>;
			platform::SdlRendererDeviceObPtr renderer_ptr;
			resource::ResourceManager& resource_manager_borrowed;
			TextureManager texture_manager;

		public:
			SdlRenderer(platform::SdlRendererDeviceObPtr renderer, resource::ResourceManager& manager);
			~SdlRenderer()override = default;

			SdlRenderer(const SdlRenderer&) = delete;
			SdlRenderer& operator=(const SdlRenderer&) = delete;
			SdlRenderer(SdlRenderer&&) = default;
			SdlRenderer& operator=(SdlRenderer&&) = default;

			void renderTest()const;
			auto render(const std::span<const RenderCommand2D>& commands)-> std::expected<void, RendererError>override;
			void drawTexture(
				const Camera2DManager& camera_manager, const Sprite& sprite, const core::Vector2& position,
				const core::Vector2& scale = { 1.0f, 1.0f }, double angle = 0.0f, SDL_FlipMode flip_mode = SDL_FlipMode::SDL_FLIP_NONE
			)const;
			void drawTexture(const SpriteRenderCommand& command);

			platform::SdlRendererDeviceObPtr getRendererPtr()const;

			//std::expected<void, RendererError> submit(const RenderCommand2D& render_command_2d) override;
			void beginFrame() override;
			void clear() override;
			std::expected<void, RendererError> execute(const RenderCommand2D& render_command_2d)override;
			void present() override;
			void endFrame() override;
			
	};

	SdlRenderer::SdlRenderer(
		platform::SdlRendererDeviceObPtr renderer,
		resource::ResourceManager& manager
	):	
		renderer_ptr(renderer),
		resource_manager_borrowed(manager),
		texture_manager(*renderer, manager)
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

	auto SdlRenderer::render(const std::span<const RenderCommand2D>& commands)->std::expected<void, RendererError>
	{
		auto t0 = std::chrono::steady_clock::now();
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
		auto t1 = std::chrono::steady_clock::now();
		present();
		auto t2 = std::chrono::steady_clock::now();
		endFrame();
		std::println(
			"end commands={} execute={}us present={}us",
			commands.size(),
			std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count(),
			std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count()
		);

		return {};
	}

	void SdlRenderer::drawTexture(
		const Camera2DManager& camera_manager, const Sprite& sprite, const core::Vector2& position,
		const core::Vector2& scale, double angle, SDL_FlipMode flip_mode
	)const
	{
		auto screen_position = camera_manager.worldToScreen(position);

		// acquire SDL_Texture
		// compute rectangle and call SDL_RenderTextureRotated()s
		SDL_RenderTextureRotated(renderer_ptr.get(), resource::SdlTexturePtr{}.get(),
			nullptr, nullptr, angle, nullptr, flip_mode
		);
	}

	void SdlRenderer::drawTexture(const SpriteRenderCommand& command)
	{
		auto image_handle = command.sprite.getImageHandle();
		auto image = resource_manager_borrowed.getImage(image_handle);
		auto texture_result = texture_manager.findTexture(image_handle);
		if (!texture_result)
		{
			std::println("HandleError:{}", static_cast<int>(texture_result.error()));
			texture_manager.loadTexture(image_handle);
			return;
		}
		auto texture = texture_manager.getTexture(texture_result.value());

		if (!texture)
		{
			std::println("RendererError:{}", static_cast<int>(texture.error()));
			return;
		}

		const auto source_rect = command.sprite.getSourceRect();
		const auto textureSize = resource_manager_borrowed.getImageSize(image.value().get());

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

	platform::SdlRendererDeviceObPtr SdlRenderer::getRendererPtr()const
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

