module;

export module engine.render.apprenderer;
import :spriterenderer;
import :primitiverenderer;
import :meshrenderer;

import engine.render.framerecorder;
import engine.render.sprite;
import engine.render.mesh;
import engine.render.camera;
import engine.core.math;
import engine.utilities;
import std;

export namespace engine::render
{
	struct AppRenderer
	{
		private:
			utilities::ObPtr<FrameRecorder> m_recorder_;
			SpriteRenderer m_sprite_renderer_;
			PrimitiveRenderer m_primitive_renderer_;
			MeshRenderer m_mesh_renderer_;

		public:
			explicit AppRenderer(FrameRecorder& recorder);
			
			auto drawSprite(const Sprite& sprite, const math::Transform2D& transform, FlipMode flip_mode) const -> std::expected<void, ERendererError>;

			auto drawRectangle(const Rect2DCommand& rect_2d, const math::Transform2D& transform) const -> std::expected<void, ERendererError>;

			auto drawMesh(const MeshData& mesh, const math::Transform3D& transform_3d) const -> std::expected<void, ERendererError>;

			auto drawSimpleText(const SimpleText2DCommand& text_2d, const math::Transform2D& transform2d) const -> std::expected<void, ERendererError>;

			void setActiveCamera(const Camera2D& camera2d)const;

			void setActiveCamera(const Camera3D& camera3d)const;
	};
}

namespace engine::render
{
	AppRenderer::AppRenderer(FrameRecorder& recorder) :
		m_recorder_(recorder),
		m_sprite_renderer_(util::borrow(recorder)),
		m_primitive_renderer_(util::borrow(recorder)),
		m_mesh_renderer_(util::borrow(recorder))
	{
	}

	auto AppRenderer::drawSprite(const Sprite& sprite, const math::Transform2D& transform,
		const FlipMode flip_mode) const -> std::expected<void, ERendererError>
	{
		return m_sprite_renderer_.drawSprite(sprite, transform, flip_mode);
	}

	auto AppRenderer::drawRectangle(const Rect2DCommand &rect_2d,
		const math::Transform2D &transform) const -> std::expected<void, ERendererError>
	{
		return m_primitive_renderer_.drawRectangle(rect_2d, transform);
	}

	auto AppRenderer::drawMesh(const MeshData &mesh,
		const math::Transform3D &transform_3d) const -> std::expected<void, ERendererError>
	{
		return m_mesh_renderer_.drawMesh(mesh, transform_3d);
	}

	auto AppRenderer::drawSimpleText(const SimpleText2DCommand& text_2d,
		const math::Transform2D& transform2d) const -> std::expected<void, ERendererError>
	{
		return m_primitive_renderer_.drawSimpleText(text_2d, transform2d);
	}

	void AppRenderer::setActiveCamera(const Camera2D& camera2d)const
	{
		m_recorder_->setCamera(camera2d);
	}

	void AppRenderer::setActiveCamera(const Camera3D& camera3d)const
	{
		m_recorder_->setCamera(camera3d);
	}
}
