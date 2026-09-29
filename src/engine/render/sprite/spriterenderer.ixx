module;

export module engine.render.apprenderer:spriterenderer;

import engine.resource.resourcemanager;
import engine.render.rendererbackend;
import engine.render.framerecorder;
import engine.render.framedata;
import engine.render.sprite;
import engine.utilities;
import engine.core.math;
import std;


export namespace engine::render
{
    class SpriteRenderer
    {
	    private:
			utilities::ObPtr<FrameRecorder> recorder_borrowed;

	    public:
	        SpriteRenderer(utilities::BrPtr<FrameRecorder> recorder);

			SpriteRenderer(const SpriteRenderer&) = delete;
			SpriteRenderer& operator=(const SpriteRenderer&) = delete;
			SpriteRenderer(SpriteRenderer&&) = delete;
			SpriteRenderer& operator=(SpriteRenderer&&) = delete;

			std::expected<void, ERendererError> drawSprite(
				const Sprite& sprite, const core::Transform2D& transform,
				FlipMode flip_mode
			)const;
			std::expected<void, ERendererError> drawSprite(
				const Sprite& sprite, const core::Vector2& position,
				const core::Vector2& scale, float rotation, FlipMode flip_mode
			)const;
    };
}

namespace engine::render
{
	SpriteRenderer::SpriteRenderer(const utilities::BrPtr<FrameRecorder> recorder)
	: recorder_borrowed(recorder.get())
	{
	}

	std::expected<void, ERendererError> SpriteRenderer::drawSprite(
		const Sprite& sprite,
		const core::Transform2D& transform,
		FlipMode flip_mode
	)const
	{
		recorder_borrowed->record(
			SpriteRenderCommand{
				.sprite = sprite,
				.transform_2d = transform,
				.flip_mode = flip_mode
			}
		);
		return{};
	}

	std::expected<void, ERendererError> SpriteRenderer::drawSprite(
		const Sprite& sprite, const core::Vector2& position,
		const core::Vector2& scale, float rotation, FlipMode flip_mode
	)const
	{
		recorder_borrowed->record(
			SpriteRenderCommand{
				.sprite = sprite,
				.transform_2d = core::Transform2D{
					.position = position,
					.rotation = rotation,
					.scale = scale
				},
				.flip_mode = flip_mode
			}
		);
		return{};
	}
}
