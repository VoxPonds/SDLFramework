module;

export module engine.render.apprenderer;
import :spriterenderer;
import engine.render.framerecorder;
import engine.render.sprite;
import engine.render.camera;
import engine.core.math;
import std;

export namespace engine::render
{
	struct AppRenderer
	{
		private:
			utilities::ObPtr<FrameRecorder> recorder_;
			SpriteRenderer sprite_renderer_;

		public:
			AppRenderer(FrameRecorder& recorder);
			
			auto drawSprite(const Sprite& sprite, const core::Transform2D& transform, FlipMode flip_mode) -> std::expected<void, RendererError>;
			void setActiveCamera(const Camera2D& camera2d)const;
			void setActiveCamera(const Camera3D& camera3d)const;
	};

	AppRenderer::AppRenderer(FrameRecorder& recorder):
		recorder_(recorder),
		sprite_renderer_(recorder)
	{
	}

	auto AppRenderer::drawSprite(
		const Sprite& sprite, 
		const core::Transform2D& transform,
		FlipMode flip_mode) -> std::expected<void, RendererError>
	{
		return sprite_renderer_.drawSprite(sprite, transform, flip_mode);
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
