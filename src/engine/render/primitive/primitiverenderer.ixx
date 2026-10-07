module;

export module engine.render.apprenderer:primitiverenderer;
import engine.utilities;
import engine.render.framerecorder;
import engine.render.framedata;
import engine.core.math;
import std;

export namespace engine::render
{
    enum class EPrimitiveTypes
    {
        LINE,
        TRIANGLE,
        RECTANGLE,
        CIRCLE,
    };

    class PrimitiveRenderer
    {
        private:
            utilities::ObPtr<FrameRecorder> m_recorder_borrowed_;

        public:
            explicit PrimitiveRenderer(utilities::BrPtr<FrameRecorder> recorder);

            auto drawRectangle(const Rect2DCommand& rect_2d, const math::Transform2D& transform) const -> std::expected<void, ERendererError>;

            auto drawPrimitive(EPrimitiveTypes type, const math::Transform2D& transform2d) const -> std::expected<void, ERendererError>;

            auto drawSimpleText(const SimpleText2DCommand& text_2d, const math::Transform2D& transform2d) const -> std::expected<void, ERendererError>;

            PrimitiveRenderer(const PrimitiveRenderer& other) = delete;
            PrimitiveRenderer(PrimitiveRenderer&& other) noexcept = delete;
            PrimitiveRenderer& operator=(const PrimitiveRenderer& other) = delete;
            PrimitiveRenderer& operator=(PrimitiveRenderer&& other) noexcept = delete;

    };
}

namespace engine::render
{
    auto PrimitiveRenderer::drawRectangle(const Rect2DCommand& rect_2d,
        const math::Transform2D& transform) const -> std::expected<void, ERendererError>
    {
        m_recorder_borrowed_->record(
            PrimitiveCommand2D{
                .primitive_2D = rect_2d,
                .transform_2d = transform,
            }
        );
        return {};
    }

    PrimitiveRenderer::PrimitiveRenderer(const utilities::BrPtr<FrameRecorder> recorder):
        m_recorder_borrowed_(recorder.get())
    {
    }

    auto PrimitiveRenderer::drawPrimitive(EPrimitiveTypes type,
        const math::Transform2D& transform2d) const -> std::expected<void, ERendererError>
    {
        m_recorder_borrowed_->record(
            PrimitiveCommand2D{
                .primitive_2D = Rect2DCommand{},
                .transform_2d = transform2d,
            }
        );
        return {};
    }

    auto PrimitiveRenderer::drawSimpleText(const SimpleText2DCommand &text_2d,
        const math::Transform2D& transform2d) const -> std::expected<void, ERendererError>
    {
        m_recorder_borrowed_->record(
            PrimitiveCommand2D{
                .primitive_2D = text_2d,
                .transform_2d = transform2d,
            }
        );
        return {};
    }
}
