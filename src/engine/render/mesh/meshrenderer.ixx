module;

export module engine.render.apprenderer:meshrenderer;

import engine.render.mesh;
import engine.render.framedata;
import engine.render.framerecorder;
import engine.core.math;
import engine.utilities;
import std;

export namespace engine::render
{
    class MeshRenderer
    {
        private:
            util::ObPtr<FrameRecorder> m_recorder_borrowed_;

        public:
            explicit MeshRenderer(util::BrPtr<FrameRecorder> recorder);
            ~MeshRenderer() = default;
            MeshRenderer(const MeshRenderer& other) = delete;
            MeshRenderer& operator=(const MeshRenderer& other) = delete;
            MeshRenderer(MeshRenderer&& other) noexcept = delete;
            MeshRenderer& operator=(MeshRenderer&& other) noexcept = delete;

            auto drawMesh(const MeshData& mesh,
                const math::Transform3D& transform_3d) const -> std::expected<void, ERendererError>;
            auto drawMesh(const MeshRenderCommand& mesh_command) const -> std::expected<void, ERendererError>;
    };


}

namespace engine::render
{
    MeshRenderer::MeshRenderer(const util::BrPtr<FrameRecorder> recorder)
        : m_recorder_borrowed_(recorder.get())
    {
    }

    auto MeshRenderer::drawMesh(const MeshData& mesh,
        const math::Transform3D& transform_3d) const -> std::expected<void, ERendererError>
    {
        m_recorder_borrowed_->record(
            MeshRenderCommand{
                .mesh = mesh,
                .transform_3d = transform_3d,
            }
        );
        return {};
    }

    auto MeshRenderer::drawMesh(const MeshRenderCommand& mesh_command) const -> std::expected<void, ERendererError>
    {
        m_recorder_borrowed_->record(
            RenderCommand3D{
                std::in_place_type<std::remove_cvref_t<decltype(mesh_command)>>,
                mesh_command.mesh,
                mesh_command.transform_3d
            }
        );
        return {};
    }
}
