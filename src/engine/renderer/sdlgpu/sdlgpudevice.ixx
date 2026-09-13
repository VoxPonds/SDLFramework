module;
#include "SDL3/SDL_gpu.h"

export module engine.render.sdlgpudevice;

import engine.render.rendertypes;
import engine.render.sdlgpucommandcontext;
import engine.platform.sdlptr;
import engine.resource.resourceptr;
import engine.resource.resourcetraits;
import std;

export namespace engine::render
{
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
    inline std::vector<std::uint8_t> readBinaryFile(const std::filesystem::path& path);
    inline SDL_GPUShader* loadShader(SDL_GPUDevice* device, const std::filesystem::path& path, const SDL_GPUShaderStage stage);
    class SdlGpuDevice
    {
        private:
            platform::SdlGpuDevicePtr sdl_gpu_device;
            platform::WindowObPtr window_borrowed;
            RenderCapabilities capabilities_;

        public:
            explicit SdlGpuDevice(SDL_Window& window);
            ~SdlGpuDevice();

            platform::SdlGpuDeviceObPtr device() const;
            platform::WindowObPtr window() const;

            auto createShader(const std::filesystem::path& path,
                SDL_GPUShaderStage stage) const -> std::expected<resource::SdlGpuShaderPtr, EGpuError>;

            auto createGpuBuffer(const SDL_GPUBufferCreateInfo& buffer_info) const -> std::expected<resource::SdlGpuBufferPtr, EGpuError>;

            auto acquireCommandBuffer() const -> std::expected<platform::GPUCommandBufferObPtr, EGpuError>;

            auto createGraphicsPipeline( const SDL_GPUGraphicsPipelineCreateInfo& info)
                const ->std::expected<resource::SdlGpuGraphicsPipelinePtr, EGpuError>;

            RenderCapabilities getCapabilities();
    };
}
