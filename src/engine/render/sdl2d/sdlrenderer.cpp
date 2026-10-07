module;
#include "SDL3/SDL_render.h"
#include "glm/glm.hpp"

module engine.render.sdlrenderer;

namespace engine::render
{
    SdlRenderer::SdlRenderer(
		platform::SdlRendererDeviceObPtr renderer,
		resource::ResourceManager& manager
	):
		renderer_ptr(renderer),
		resource_manager_borrowed(manager),
		texture_manager(*renderer, manager)
	{

	}

	auto SdlRenderer::render(const FrameData& data)->std::expected<void, ERendererError>
	{
		auto t0 = std::chrono::steady_clock::now();
		auto commands = data.command2ds_.commands();
		auto& camera = data.camera;
		beginFrame();
		clear();
		for (const auto& command : commands)
		{

			auto state = execute(camera, command);

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
		/*std::println(
			"end commands={} execute={}us present={}us",
			commands.size(),
			std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count(),
			std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count()
		);*/

		return {};
	}

	void SdlRenderer::drawRect(const Camera2D &camera, const Rect2DCommand &command, const math::Transform2D& transform2d) const
	{
    	const auto& [rect_pos, rect_size] = command.rect;
    	const auto& [red, green, blue, alpha] = command.color;

    	const SDL_FRect rect{
    		.x = rect_pos.x,
			.y = rect_pos.y,
			.w = rect_size.x,
			.h = rect_size.y,
		};

    	if (!SDL_SetRenderDrawColorFloat(
			renderer_ptr.get(),
			red,
			green,
			blue,
			alpha
		))
    	{
    		std::println("SDL_SetRenderDrawColorFloat failed: {}", SDL_GetError());
    	}

	    if (command.filled)
    	{
    		SDL_RenderFillRect(
				renderer_ptr.get(),
				&rect
			);
    	}
    	else
    	{
    		SDL_RenderRect(
				renderer_ptr.get(),
				&rect
			);
    	}
	}

	void SdlRenderer::drawSimpleText(const Camera2D& camera, const SimpleText2DCommand& command, const math::Transform2D& transform2d) const
	{
    	const auto position = transform2d.position;
    	const std::string text {command.text};

	    constexpr auto scale = 2.0f;
    	float r {};
    	float g {};
    	float b {};
    	float a {};

    	SDL_GetRenderDrawColorFloat(renderer_ptr.get(), &r, &g, &b, &a);
    	SDL_SetRenderScale(renderer_ptr.get(), scale, scale);
    	auto [dr,dg,db,da] = command.color;
    	SDL_SetRenderDrawColorFloat(renderer_ptr.get(), dr, dg, db, da);

    	if (!SDL_RenderDebugText(
			renderer_ptr.get(),
			position.x/scale,
			position.y/scale,
			text.c_str()
		))
    	{
    		std::println("SDL_RenderDebugText failed: {}", SDL_GetError());
    	}

    	SDL_SetRenderScale(renderer_ptr.get(), 1.0, 1.0f);
    	SDL_SetRenderDrawColorFloat(renderer_ptr.get(), r, g, b, a);
	}

	void SdlRenderer::drawTexture(const Camera2D& camera, const SpriteRenderCommand& command)
	{
		const auto image_handle = command.sprite.getImageHandle();
		const auto image = resource_manager_borrowed.getImage(image_handle);

		auto texture_result = texture_manager.findTexture(image_handle);
		if (!texture_result)
		{
			std::println("HandleError:{}", std::to_underlying(texture_result.error()));
			if (const auto load_result = texture_manager.loadTexture(image_handle); !load_result) {}
			return;
		}

		auto texture = texture_manager.getTexture(texture_result.value());

		if (!texture)
		{
			std::println("RendererError:{}", std::to_underlying(texture.error()));
			return;
		}

		const auto source_rect = command.sprite.getSourceRect();
		const auto texture_size = resource_manager_borrowed.getImageSize(resource::ImageObPtr(image.value().get()));

		const SDL_FRect* src_rect;

		if (source_rect)
		{
			const SDL_FRect temp_rect{
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

		const math::Vector2 source_size =
			source_rect
			? math::Vector2{
					source_rect->size.x,
					source_rect->size.y
				}
			: texture_size.value();

		const auto screen_position = camera.worldToScreen(command.transform_2d.position);

		const SDL_FRect temp_rect{
			.x = static_cast<float>(screen_position.x),
			.y = static_cast<float>(screen_position.y),
			.w = static_cast<float>(
				source_size.x * command.transform_2d.scale.x
			),
			.h = static_cast<float>(
				source_size.y * command.transform_2d.scale.y
			)
		};

		const SDL_FRect* dst_rect = &temp_rect;

		if (const auto flip_mode = static_cast<SDL_FlipMode>(command.flip_mode); !SDL_RenderTextureRotated
			(
				renderer_ptr.get(),
				texture.value().get(),
				src_rect,
				dst_rect,
				command.transform_2d.rotation,
				nullptr,
				flip_mode
			)
		)
		{
			std::println("SDL_RenderTextureRotated failed: {}", SDL_GetError());
		}
	}

	void SdlRenderer::drawTexture(const SpriteRenderCommand& command)
	{
		auto image_handle = command.sprite.getImageHandle();
		auto image = resource_manager_borrowed.getImage(image_handle);
		auto texture_result = texture_manager.findTexture(image_handle);
		if (!texture_result)
		{
			std::println("HandleError:{}", std::to_underlying(texture_result.error()));
			if (const auto load_result = texture_manager.loadTexture(image_handle); !load_result)
				return;
		}
		auto texture = texture_manager.getTexture(texture_result.value());

		if (!texture)
		{
			std::println("RendererError:{}", std::to_underlying(texture.error()));
			return;
		}

		const auto source_rect = command.sprite.getSourceRect();
		const auto textureSize = resource_manager_borrowed.getImageSize(resource::ImageObPtr(image.value().get()));

		SDL_FRect *src_rect;

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

		const math::Vector2 source_size =
			source_rect
			? math::Vector2{
				source_rect->size.x,
				source_rect->size.y
			}
			: textureSize.value();

		SDL_FRect *dst_rect;
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
				texture->get(),
				src_rect,
				dst_rect,
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
		SDL_SetRenderDrawColor(
			renderer_ptr.get(),
			0,
			0,
			0,
			255
		);
		SDL_RenderClear(renderer_ptr.get());
	}

	auto SdlRenderer::execute(const Camera& camera, const RenderCommand2D& render_command_2d) -> std::expected<void, ERendererError>
	{
    	if (!std::holds_alternative<Camera2D>(camera))
    	{
    		return std::unexpected(ERendererError::INVALID_CAMERA);
    	}
    	const auto& camera_2d = std::get<Camera2D>(camera);

		std::visit(
		[&]<typename T>(T&& command_) -> void
			{
    			using DT = std::remove_cvref_t<T>;
				if constexpr (std::is_same_v<DT, SpriteRenderCommand>)
				{
					drawTexture(camera_2d, std::forward<T>(command_));
				}
				else if constexpr (std::is_same_v<DT, PrimitiveCommand2D>)
				{
					if(const auto rect_command = std::get_if<Rect2DCommand>(&command_.primitive_2D); rect_command)
					{
						drawRect(camera_2d, *rect_command, command_.transform_2d);
					}
					if(const auto text_command = std::get_if<SimpleText2DCommand>(&command_.primitive_2D); text_command)
					{
						drawSimpleText(camera_2d, *text_command, command_.transform_2d);
					}
				}
			},
			render_command_2d
		);
		return std::expected<void, ERendererError>(std::in_place);
	}

	void SdlRenderer::present()
	{
		SDL_RenderPresent(renderer_ptr.get());
	}

	void SdlRenderer::endFrame()
	{
	}

	void SdlRenderer::renderTest() const
    {
    	constexpr auto message = "Hello World!";
    	int w = 0, h = 0;
    	constexpr float scale = 4.0f;
    	SDL_SetRenderLogicalPresentation(getRendererPtr().get(), 1280, 720, SDL_LOGICAL_PRESENTATION_LETTERBOX);
    	/* Center the message and scale it up */
    	SDL_GetRenderOutputSize(renderer_ptr.get(), &w, &h);
    	SDL_SetRenderScale(renderer_ptr.get(), scale, scale);
    	const float x = (w / scale - SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE * SDL_strlen(message)) / 2;
    	const float y = (h / scale - SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE) / 2;

    	/* Draw the message */
    	SDL_SetRenderDrawColor(renderer_ptr.get(), 0, 0, 0, 255);
    	SDL_RenderClear(renderer_ptr.get());
    	SDL_SetRenderDrawColor(renderer_ptr.get(), 255, 255, 255, 255);
    	SDL_RenderDebugText(renderer_ptr.get(), x, y, message);
    	SDL_RenderPresent(renderer_ptr.get());
    }
}