module;

export module engine.renderer.spriterenderer;

import engine.resource.resourcemanager;
import engine.renderer.renderer;
import engine.renderer.sprite;
import engine.utilities;
import engine.core.math;
import std;


export namespace engine::renderer
{
    class SpriteRenderer
    {
	    private:
			RenderObPtr renderer_borrowed;

	    public:
	        SpriteRenderer(RenderObPtr renderer);

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

    SpriteRenderer::SpriteRenderer(RenderObPtr renderer)
		: renderer_borrowed(renderer)
    {
    }

    std::expected<void, RendererError> SpriteRenderer::drawSprite(
    	const Sprite& sprite,
	    const core::Transform2D& transform, 
	    FlipMode flip_mode
	) 
    {
		return renderer_borrowed->submit(
			SpriteRenderCommand{
				.sprite = sprite,
				.transform_2d = transform,
				.flip_mode = flip_mode
			}
		);
	}

	std::expected<void, RendererError> SpriteRenderer::drawSprite(
		const Sprite& sprite, const core::Vector2& position,
		const core::Vector2& scale, double rotation, FlipMode flip_mode
    )
	{
		return renderer_borrowed->submit(
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
	}
}
