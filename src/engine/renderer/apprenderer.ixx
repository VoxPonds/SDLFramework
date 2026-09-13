module;

export module engine.render.apprenderer;
import :spriterenderer;
import :primitiverenderer;
import engine.render.framerecorder;
import engine.render.sprite;
import engine.render.camera;
import engine.core.math;
import engine.utilities;
import std;

export namespace engine::render
{
	struct AppRenderer
	{
		private:
			utilities::ObPtr<FrameRecorder> recorder_;
			SpriteRenderer sprite_renderer_;
			PrimitiveRenderer primitive_renderer_;

		public:
			explicit AppRenderer(FrameRecorder& recorder);
			
			auto drawSprite(const Sprite& sprite, const core::Transform2D& transform,
				FlipMode flip_mode) const -> std::expected<void, ERendererError>;
			auto drawRectangle(const DrawRect2D& rect_2d,
				const core::Transform2D& transform) const -> std::expected<void, ERendererError>;

			void setActiveCamera(const Camera2D& camera2d)const;
			void setActiveCamera(const Camera3D& camera3d)const;
	};
}

namespace engine::render
{
	AppRenderer::AppRenderer(FrameRecorder& recorder) :
		recorder_(recorder),
		sprite_renderer_(utilities::borrow(recorder)),
		primitive_renderer_(utilities::borrow(recorder))
	{
	}

	auto AppRenderer::drawSprite(const Sprite& sprite, const core::Transform2D& transform,
		const FlipMode flip_mode) const -> std::expected<void, ERendererError>
	{
		return sprite_renderer_.drawSprite(sprite, transform, flip_mode);
	}

	auto AppRenderer::drawRectangle(const DrawRect2D &rect_2d,
		const core::Transform2D &transform) const -> std::expected<void, ERendererError>
	{
		return primitive_renderer_.drawRectangle(rect_2d, transform);
	}

	void AppRenderer::setActiveCamera(const Camera2D& camera2d)const
	{
		recorder_->setCamera(camera2d);
	}

	void AppRenderer::setActiveCamera(const Camera3D& camera3d)const
	{
		recorder_->setCamera(camera3d);
	}
}
