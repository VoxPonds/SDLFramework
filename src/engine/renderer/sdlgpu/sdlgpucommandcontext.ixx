module;
#include "SDL3/SDL_gpu.h"

export module engine.render.sdlgpucommandcontext;
import engine.resource.resourceptr;
import engine.platform.sdlptr;
import std;

export namespace engine::render
{
    enum class EGpuError : std::uint8_t
    {
        UNKNOWN,
        INITIALIZATION_FAILED,
        DEVICE_CREATION_FAILED,
        SHADER_COMPILATION_FAILED,
        BUFFER_CREATION_FAILED,
        BUFFER_SIZE_TOO_LARGE,
        GPU_TRANSFER_BUFFER_CREATE_FAILED,
        GPU_TRANSFER_BUFFER_MAPPING_CREATE_FAILED,
        GPU_COPY_PASS_BEGIN_FAILED,
        GPU_RENDER_PASS_BEGIN_FAILED,
        RESOURCE_CREATION_FAILED,
        GRAPHICS_PIPELINE_CREATION_FAILED,
        SUBMIT_GPU_COMMAND_BUFFER_FAILED,

        COMMAND_RECORDING_FAILED,
        COMMAND_SUBMISSION_FAILED,
        PRESENTATION_FAILED,
        INVALID_OPERATION,
    };

    class SdlGpuCommandContext
    {
        private:
            platform::SdlGpuDeviceObPtr device_;
            platform::GPUCommandBufferObPtr command_buffer_;

            auto beginCopyPass() const -> std::expected<SDL_GPUCopyPass*, EGpuError>;
            static void endCopyPass(SDL_GPUCopyPass* copy_pass);
        
            auto beginRenderPass(const SDL_GPUColorTargetInfo& color_target) const -> std::expected<SDL_GPURenderPass*, EGpuError>;
            static void endRenderPass(SDL_GPURenderPass* render_pass);

        public:
            explicit SdlGpuCommandContext(platform::SdlGpuDeviceBrPtr device,
                platform::GPUCommandBufferBrPtr command_buffer);

            template <typename T> requires std::is_trivially_copyable_v<T>
            auto uploadBuffer(resource::SdlGpuBufferBrPtr buffer,
                std::span<const T> data) -> std::expected<void, EGpuError>;

            auto uploadBufferBytes(resource::SdlGpuBufferBrPtr gpu_buffer,
                std::span<const std::byte> byte_data) const -> std::expected<void, EGpuError>;

            auto draw(const SDL_GPUColorTargetInfo& color_target,
                resource::SdlGpuGraphicsPipelineBrPtr pipeline,
                resource::SdlGpuBufferBrPtr gpu_buffer,
                std::uint32_t vertex_count) const -> std::expected<void, EGpuError>;

            /*auto bindPipeline();
            auto bindVertexBuffer();*/
    };

    template<typename T> requires std::is_trivially_copyable_v<T>
    auto SdlGpuCommandContext::uploadBuffer(const resource::SdlGpuBufferBrPtr buffer,
        std::span<const T> data) -> std::expected<void, EGpuError>
    {
        return uploadBufferBytes(buffer,std::as_bytes(data));
    }
}

