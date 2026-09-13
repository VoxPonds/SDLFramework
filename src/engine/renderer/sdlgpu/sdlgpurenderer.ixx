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
        RECORDING,
    };
    class SdlGpuRenderer
    {
        private:
            utilities::ObserverPtr<SdlGpuDevice> device_wrapper_;
            platform::SdlGpuDeviceObPtr device_;
            resource::ResourceManager& resource_manager_borrowed_;
            //platform::GPUCommandBufferObPtr command_buffer_;
            std::optional<SdlGpuCommandContext> command_context_;
            resource::SdlGpuTextureObPtr swapchain_texture_;
            EFrameState frame_state_;

        public:
            SdlGpuRenderer(utilities::BorrowedPtr<SdlGpuDevice> device, resource::ResourceManager& manager);

            auto beginFrame() const -> std::expected<void, EGpuError>;

            auto clear() -> std::expected<void, EGpuError>;

            auto endFrame() -> std::expected<void, EGpuError>;

            auto execute(const RenderCommand3D &render_command_3d) -> std::expected<void, EGpuError>;

            auto submit(platform::GPUCommandBufferBrPtr command_buffer) -> std::expected<void, EGpuError>;

            auto renderTest() -> std::expected<void, EGpuError>;

            auto render(const FrameData &data) -> std::expected<void, ERendererError>;
    };
}


