module;
#include "glm/glm.hpp"

export module engine.render.rendererbackend;
import engine.render.sprite;
import engine.render.framerecorder;
import engine.render.framedata;
import engine.utilities;
import engine.core.math;
import std;

export namespace engine::render
{
    enum class ERenderBackend : std::uint8_t
    {
	    SDL_RENDERER,
        SDL_GPU,
        VULKAN,
        BGFX,
        WEB_GPU
    };

    class IRendererBackend
    {
	    public:
	        virtual ~IRendererBackend() = default;
            virtual std::expected<void, RendererError> render(const std::span<const RenderCommand2D>& commands) = 0;
            virtual std::expected<void, RendererError> render(const std::span<const RenderCommand3D>& commands);


	        virtual void beginFrame() = 0;
	        virtual void clear() = 0;
            virtual std::expected<void, RendererError> execute(const RenderCommand2D& render_command_2d) = 0;
            virtual std::expected<void, RendererError> execute(const RenderCommand3D& render_command_3d);
	        virtual void present() = 0;
            virtual void endFrame() = 0;
    };

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
