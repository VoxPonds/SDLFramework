module;

export module engine.render.framedata;
import engine.render.sprite;
import engine.render.rendercommandqueue;
import engine.render.camera;
import engine.render.rendertypes;
import engine.core.math;
import std;

export namespace engine::render
{
    struct SpriteRenderCommand
    {
        const Sprite sprite;
        core::Transform2D transform_2d;
        FlipMode flip_mode;
        ERenderPass pass{ERenderPass::SPRITE_WORLD};
    };

    struct DrawRect2D
    {
        core::FrothRect rect;
        core::FrothColor color;
        bool filled;
    };

    struct PrimitiveCommand2D
    {
        std::variant<DrawRect2D> primitive_2D;
        core::Transform2D transform_2d;
    };

    struct MeshRenderCommand
    {

    };

    using RenderCommand2D = std::variant<
	    SpriteRenderCommand,
        PrimitiveCommand2D,
	    std::monostate
    >;


    using RenderCommand3D = std::variant <
        MeshRenderCommand,
        std::monostate
    >;

    struct FrameData
    {
        std::variant<Camera2D, Camera3D> camera;
        RenderCommandQueue<RenderCommand2D> command2ds_;
        RenderCommandQueue<RenderCommand3D> command3ds_;

        void add(const RenderCommand2D& command);
        void add(const RenderCommand3D& command);
        void clear();
    };


}

namespace engine::render
{
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
