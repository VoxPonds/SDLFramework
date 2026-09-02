module;
#include <variant>

export module engine.render.framedata;
import engine.render.sprite;
import engine.render.rendercommandqueue;
import engine.core.math;


export namespace engine::render
{
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

    struct FrameData
    {
        RenderCommandQueue<RenderCommand2D> command2ds_;
        RenderCommandQueue<RenderCommand3D> command3ds_;

        void add(const RenderCommand2D& command);
        void add(const RenderCommand3D& command);
        void clear();
    };

    void FrameData::add(const RenderCommand2D& command)
    {
        command2ds_.insert(command);
    }

    void FrameData::add(const RenderCommand3D& command)
    {
        command3ds_.insert(command);
    }

    void FrameData::clear()
    {
        command2ds_.clear();
        command3ds_.clear();
    }
}
