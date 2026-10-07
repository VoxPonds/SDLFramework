module;

export module engine.render.sdlgpurenderer;

import engine.platform.sdlptr;
import engine.render.rendererbackend;
import engine.render.sdlgpucommandcontext;
import engine.render.framerecorder;
import engine.render.framedata;
import engine.render.camera;
import engine.render.sdlgpudevice;
import engine.resource.resourcemanager;
import engine.resource.resourceptr;
import engine.utilities;
import std;

export namespace engine::render
{
    enum class EFrameState : std::uint8_t
    {
        IDLE,
        BEGUN,
        RECORDING,
    };

    inline auto toRendererError(const EGpuError error) -> ERendererError
    {
        switch (error)
        {
            case EGpuError::INITIALIZATION_FAILED:
            case EGpuError::DEVICE_CREATION_FAILED:
            case EGpuError::SHADER_COMPILATION_FAILED:
            case EGpuError::BUFFER_CREATION_FAILED:
            case EGpuError::BUFFER_SIZE_TOO_LARGE:
            case EGpuError::GPU_TRANSFER_BUFFER_CREATE_FAILED:
            case EGpuError::GPU_TRANSFER_BUFFER_MAPPING_CREATE_FAILED:
            case EGpuError::GPU_COPY_PASS_BEGIN_FAILED:
            case EGpuError::GPU_RENDER_PASS_BEGIN_FAILED:
            case EGpuError::RESOURCE_CREATION_FAILED:
            case EGpuError::GRAPHICS_PIPELINE_CREATION_FAILED:
            case EGpuError::SUBMIT_GPU_COMMAND_BUFFER_FAILED:
            case EGpuError::COMMAND_RECORDING_FAILED:
            case EGpuError::COMMAND_SUBMISSION_FAILED:
            case EGpuError::PRESENTATION_FAILED:
            case EGpuError::INVALID_OPERATION:
            case EGpuError::INVALID_FRAME_STATE:
            case EGpuError::ACQUIRE_SWAPCHAIN_TEXTURE_FAILED:
                return ERendererError::GPU_FAILURE;
            default: std::unreachable();
        }
    }

    struct Vertex
    {
        float x;
        float y;
        float z;
    };

    constexpr std::array vertices{
        Vertex{  .x = 0.0f, .y = -0.5f, .z = 0.0f },
        Vertex{  .x = 0.5f,  .y = 0.5f, .z = 0.0f },
        Vertex{  .x = -0.5f,  .y = 0.5f, .z = 0.0f }
    };

    class SdlGpuRenderer
    {
        private:
            utilities::ObserverPtr<SdlGpuDevice> m_device_wrapper_;
            platform::SdlGpuDeviceObPtr m_device_;
            resource::ResourceManager& m_resource_manager_borrowed_;

            platform::SdlGpuCommandBufferObPtr m_command_buffer_;
            std::optional<SdlGpuCommandContext> m_command_context_;
            resource::SdlGpuTextureObPtr m_swapchain_texture_;

            resource::SdlGpuShaderPtr m_vertex_shader_;
            resource::SdlGpuShaderPtr m_fragment_shader_;
            resource::SdlGpuBufferPtr m_gpu_buffer_;
            resource::SdlGpuGraphicsPipelinePtr m_pipeline_;

            EFrameState m_frame_state_;
            std::uint32_t m_frame_width_{};
            std::uint32_t m_frame_height_{};

        public:
            SdlGpuRenderer(util::BorrowedPtr<SdlGpuDevice> device, resource::ResourceManager& manager);

            auto render(const FrameData &data) -> std::expected<void, ERendererError>;

            auto initialize() -> std::expected<void, EGpuError>;

            auto beginFrame() -> std::expected<void, EGpuError>;

            auto clear() -> std::expected<void, EGpuError>;

            auto execute(const Camera& camera, std::span<const RenderCommand3D> command_3d_list) -> std::expected<void, EGpuError>;

            auto endFrame() -> std::expected<void, EGpuError>;

            auto submit(platform::SdlGpuCommandBufferBrPtr command_buffer) -> std::expected<void, EGpuError>;

            auto renderTest() -> std::expected<void, EGpuError>;
    };
}


