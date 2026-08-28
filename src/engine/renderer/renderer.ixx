module;
#include "glm/glm.hpp"

export module engine.renderer.renderer;
import engine.renderer.sprite;
import :rendercommandqueue;
import engine.utilities;
import engine.core.math;
import std;

export namespace engine::renderer
{
	enum class RendererError
	{
		None,
		InvalidCommand,
		RenderFailed,
        UnsupportedCommand,
        ResourceNotFound,
        BackendError
	};

    struct SpriteRenderCommand
    {
        const Sprite sprite;
        core::Transform2D transform_2d;
    	FlipMode flip_mode;
    };

    struct MeshRenderCommand
    {
        
    };

    using RenderCommand2D = std::variant<
    	SpriteRenderCommand,
        std::monostate
	>;

    using RenderCommand3D = std::variant <
        MeshRenderCommand,
        std::monostate
    >;

    class Renderer
    {
		protected:
            RenderCommandQueue<RenderCommand2D> commands2d_;

	    public:
	        virtual ~Renderer() = default;
            virtual std::expected<void, RendererError> renderFrame() = 0;
            virtual std::expected<void, RendererError> renderFrame(const std::span<const RenderCommand2D>& commands) = 0;
            virtual std::expected<void, RendererError> submit(const RenderCommand2D& render_command_2d) = 0;
            virtual std::expected<void, RendererError> submit(const RenderCommand3D& render_command_3d);

	        virtual void beginFrame() = 0;
	        virtual void clear() = 0;
            virtual std::expected<void, RendererError> execute(const RenderCommand2D& render_command_2d) = 0;
            virtual std::expected<void, RendererError> execute(const RenderCommand3D& render_command_3d);
	        virtual void present() = 0;
            virtual void endFrame() = 0;
    };

    std::expected<void, RendererError> Renderer::submit(const RenderCommand3D& render_command_3d)
    {
        return std::unexpected(RendererError::UnsupportedCommand);
    }

    std::expected<void, RendererError> Renderer::execute(const RenderCommand3D& render_command_3d)
    {
        return std::unexpected(RendererError::UnsupportedCommand);
    }

    using RenderObPtr = utilities::ObPtr<Renderer>;
}
