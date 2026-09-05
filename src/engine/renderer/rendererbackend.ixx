module;
#include "glm/glm.hpp"

export module engine.render.rendererbackend;
import engine.render.sprite;
import engine.render.framerecorder;
import engine.render.framedata;
import engine.render.camera;
import engine.render.rendertypes;
import engine.utilities;
import engine.core.math;
import std;

export namespace engine::render
{
    class IRendererBackend
    {
	    public:
	        virtual ~IRendererBackend() = default;
            virtual std::expected<void, RendererError> render(const std::span<const RenderCommand2D>& commands);
            virtual std::expected<void, RendererError> render(const std::span<const RenderCommand3D>& commands);
            virtual std::expected<void, RendererError> render(const FrameData& data) = 0;

	        virtual void beginFrame() = 0;
	        virtual void clear() = 0;
            //virtual std::expected<void, RendererError> execute(const RenderCommand2D& render_command_2d) = 0;
            virtual std::expected<void, RendererError> execute(const RenderCommand3D& render_command_3d);
            virtual std::expected<void, RendererError> execute(const Camera& camera, const RenderCommand2D& render_command_2d)= 0;
            
            
	        virtual void present() = 0;
            virtual void endFrame() = 0;
    };

    std::expected<void, RendererError> IRendererBackend::render(const std::span<const RenderCommand2D>& commands)
    {
        return std::unexpected(RendererError::UNSUPPORTED_COMMAND);
    }

    std::expected<void, RendererError> IRendererBackend::render(const std::span<const RenderCommand3D>& commands)
    {
        return std::unexpected(RendererError::UNSUPPORTED_COMMAND);
    }

    std::expected<void, RendererError> IRendererBackend::execute(const RenderCommand3D& render_command_3d)
    {
        return std::unexpected(RendererError::UNSUPPORTED_COMMAND);
    }

    using RenderObPtr = utilities::ObPtr<IRendererBackend>;
}
