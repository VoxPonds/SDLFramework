module;

export module engine.render.spriterenderer;

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
	        SpriteRenderer(utilities::ObPtr<FrameRecorder> recorder);

			SpriteRenderer(const SpriteRenderer&) = delete;
			SpriteRenderer& operator=(const SpriteRenderer&) = delete;
			SpriteRenderer(SpriteRenderer&&) = delete;
			SpriteRenderer& operator=(SpriteRenderer&&) = delete;

			std::expected<void, RendererError> drawSprite(
				const Sprite& sprite, const core::Transform2D& transform,
				FlipMode flip_mode
			);
			std::expected<void, RendererError> drawSprite(
				const Sprite& sprite, const core::Vector2& position,
				const core::Vector2& scale, double rotation, FlipMode flip_mode
			);
    };

    SpriteRenderer::SpriteRenderer(utilities::ObPtr<FrameRecorder> recorder)
		: recorder_borrowed(recorder)
    {
    }

    std::expected<void, RendererError> SpriteRenderer::drawSprite(
    	const Sprite& sprite,
	    const core::Transform2D& transform, 
	    FlipMode flip_mode
	) 
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

	std::expected<void, RendererError> SpriteRenderer::drawSprite(
		const Sprite& sprite, const core::Vector2& position,
		const core::Vector2& scale, double rotation, FlipMode flip_mode
    )
	{
		recorder_borrowed->record(
			SpriteRenderCommand{
				.sprite = sprite,
				.transform_2d = core::Transform2D{
					.position = position,
					.scale = scale,
					.rotation = rotation
				},
				.flip_mode = flip_mode
			}
		);
		return{};
	}
}
